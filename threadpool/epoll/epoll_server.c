#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdatomic.h>

/* ================= CONFIG ================= */
#define DATA_PORT 9000
#define CTRL_PORT 9001
#define BACKLOG 65535
#define MAX_EVENTS 10000
#define BUFFER_SIZE 1024
#define WORKERS 8
#define MAX_QUEUE 200000

/* ================= GLOBAL ================= */
volatile int running = 1;

/* ================= COUNTERS ================= */
atomic_ulong accepted = 0;
atomic_ulong handled  = 0;
atomic_ulong dropped  = 0;
atomic_int   queue_sz = 0;

/* ================= TASK QUEUE ================= */
typedef struct task {
    int fd;
    struct task *next;
} task_t;

typedef struct {
    pthread_t threads[WORKERS];
    task_t *head, *tail;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int shutdown;
} pool_t;

pool_t pool;

/* ================= UTILS ================= */
int nonblock(int fd) {
    int f = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, f | O_NONBLOCK);
}

/* ================= THREAD POOL ================= */
void enqueue(int fd) {
    task_t *t = malloc(sizeof(task_t));
    if (!t) {
        dropped++;
        close(fd);
        return;
    }

    t->fd = fd;
    t->next = NULL;

    pthread_mutex_lock(&pool.lock);
    if (pool.shutdown || queue_sz >= MAX_QUEUE) {
        dropped++;
        pthread_mutex_unlock(&pool.lock);
        close(fd);
        free(t);
        return;
    }

    if (!pool.tail)
        pool.head = pool.tail = t;
    else {
        pool.tail->next = t;
        pool.tail = t;
    }

    queue_sz++;
    pthread_cond_signal(&pool.cond);
    pthread_mutex_unlock(&pool.lock);
}

task_t* dequeue() {
    task_t *t = pool.head;
    if (!t) return NULL;

    pool.head = t->next;
    if (!pool.head) pool.tail = NULL;
    queue_sz--;
    return t;
}
void* worker(void *arg) {
    (void)arg;
    char buf[BUFFER_SIZE];

    while (1) {
        pthread_mutex_lock(&pool.lock);
        while (!pool.head && !pool.shutdown)
            pthread_cond_wait(&pool.cond, &pool.lock);

        if (pool.shutdown && !pool.head) {
            pthread_mutex_unlock(&pool.lock);
            break;
        }

        task_t *t = dequeue();
        pthread_mutex_unlock(&pool.lock);

        if (!t) continue;

        int n = recv(t->fd, buf, sizeof(buf), 0);
        if (n > 0) {
            send(t->fd, buf, n, 0);
            handled++;
        } else {
            dropped++;
        }

        close(t->fd);
        free(t);
    }
    return NULL;
}

void pool_init() {
    pthread_mutex_init(&pool.lock, NULL);
    pthread_cond_init(&pool.cond, NULL);
    pool.head = pool.tail = NULL;
    pool.shutdown = 0;

    for (int i = 0; i < WORKERS; i++)
        pthread_create(&pool.threads[i], NULL, worker, NULL);
}

void pool_destroy() {
    pthread_mutex_lock(&pool.lock);
    pool.shutdown = 1;
    pthread_cond_broadcast(&pool.cond);
    pthread_mutex_unlock(&pool.lock);

    for (int i = 0; i < WORKERS; i++)
        pthread_join(pool.threads[i], NULL);

    task_t *t = pool.head;
    while (t) {
        task_t *next = t->next;
        close(t->fd);
        dropped++;
        free(t);
        t = next;
    }

    pthread_mutex_destroy(&pool.lock);
    pthread_cond_destroy(&pool.cond);
}

/* ================= CONTROL SESSION ================= */
void send_stats(int fd) {
    char out[512];
    snprintf(out, sizeof(out),
        "\nSERVER STATS\n"
        "Accepted : %lu\n"
        "Handled  : %lu\n"
        "Dropped  : %lu\n"
        "Queue    : %d\n\n",
        accepted, handled, dropped, queue_sz);
    send(fd, out, strlen(out), 0);
}

void handle_control_session(int fd) {
    char buf[256];

    send(fd, "\nWelcome to Server Control\nType 'help' for commands\n", 55, 0);

    while (running) {
        send(fd, "server> ", 8, 0);

        int n = recv(fd, buf, sizeof(buf)-1, 0);
        if (n <= 0) break;

        buf[n] = 0;
        buf[strcspn(buf, "\r\n")] = 0;  // trim newline

        if (strcmp(buf, "stats") == 0) {
            send_stats(fd);
        }
	else if(strcmp(buf, "statclr") == 0) {
	    accepted = 0;
            handled  = 0;
            dropped  = 0;
            queue_sz = 0;
	    send(fd, "Counters cleared\n", 18, 0);
	}  
	else if(strcmp(buf, "clear") == 0 || buf[0] == 0x0c) {
	    send(fd, "\033[2J\033[H", 7, 0);
	}  
        else if (strcmp(buf, "help") == 0 || strcmp(buf, "?") == 0) {
            send(fd,
                "\nCommands:\n"
                "stats        - show counters\n"
		"statclr      - clear counters\n"
		"clear|Ctrl+L - clear screen\n"
		"help|?       - list commands\n"
                "shutdown     - graceful stop\n"
                "exit         - close session\n",
                186, 0);
        }
        else if (strcmp(buf, "exit") == 0) {
            send(fd, "Bye!\n", 5, 0);
            break;
        }
        else if (strcmp(buf, "shutdown") == 0) {
            send(fd, "Shutting down server...\n", 24, 0);
            running = 0;
            //break;
        }
        else {
            send(fd, "Unknown command\n", 16, 0);
        }
    }

    close(fd);
}

void* control_thread(void *arg) {
    int fd = *(int*)arg;
    free(arg);
    handle_control_session(fd);
    return NULL;
}

/* ================= LOGO ================= */
void print_startup_log() {
    printf("Server is listening on\n");
    printf("Data port    : %d  (client traffic)\n", DATA_PORT);
    printf("Control port : %d  (telnet admin)\n", CTRL_PORT);
}

void print_shutdown_log() {
    printf("\nServer is going to shutdown");
    printf("\nSERVER STATS:\n");
    printf("Requests accepted : %lu\n", accepted);
    printf("Requests handled  : %lu\n", handled);
    printf("Requests dropped  : %lu\n", dropped);
}

/* ================= MAIN ================= */
int main() {
    pool_init();

    int data_fd = socket(AF_INET, SOCK_STREAM, 0);
    int ctrl_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    setsockopt(data_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(ctrl_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in data_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(DATA_PORT)
    };

    struct sockaddr_in ctrl_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(CTRL_PORT)
    };

    bind(data_fd, (struct sockaddr*)&data_addr, sizeof(data_addr));
    bind(ctrl_fd, (struct sockaddr*)&ctrl_addr, sizeof(ctrl_addr));

    listen(data_fd, BACKLOG);
    listen(ctrl_fd, 10);

    nonblock(data_fd);
    nonblock(ctrl_fd);

    int epfd = epoll_create1(0);
    struct epoll_event ev, events[MAX_EVENTS];

    ev.events = EPOLLIN;
    ev.data.fd = data_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, data_fd, &ev);

    ev.data.fd = ctrl_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, ctrl_fd, &ev);

    print_startup_log();

    while (running) {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);

        for (int i = 0; i < nfds; i++) {
            int fd = events[i].data.fd;

            if (fd == data_fd) {
                int cfd;
                while ((cfd = accept(data_fd, NULL, NULL)) >= 0) {
                    accepted++;
                    nonblock(cfd);
                    enqueue(cfd);
                }
            }
	    else if (fd == ctrl_fd) {
    	        int cfd;
    		while ((cfd = accept(ctrl_fd, NULL, NULL)) >= 0) {
        	    pthread_t tid;
        	    int *pfd = malloc(sizeof(int));
        	    *pfd = cfd;
        	    pthread_create(&tid, NULL, control_thread, pfd);
        	    pthread_detach(tid);  // no join needed
    	        }
	    }

        }
    }

    /* ===== SHUTDOWN ===== */
    pool_destroy();
    close(data_fd);
    close(ctrl_fd);
    close(epfd);

    print_shutdown_log();

    return 0;
}

