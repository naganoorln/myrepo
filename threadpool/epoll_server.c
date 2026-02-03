#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

/* ================= CONFIG ================= */
#define PORT 9000
#define BACKLOG 65535
#define MAX_EVENTS 100000
#define BUFFER_SIZE 1024
#define WORKERS 8

volatile sig_atomic_t running = 1;

/* ================= TASK QUEUE ================= */
typedef struct task {
    int client_fd;
    struct task *next;
} task_t;

typedef struct {
    pthread_t threads[WORKERS];
    task_t *head, *tail;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int shutdown;
} thread_pool_t;

thread_pool_t pool;

/* ================= SIGNAL ================= */
void handle_sigint(int sig) {
    running = 0;
}

/* ================= UTILS ================= */
int make_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

/* ================= THREAD POOL ================= */
void enqueue(int fd) {
    task_t *t = malloc(sizeof(task_t));
    if (!t) return;

    t->client_fd = fd;
    t->next = NULL;

    pthread_mutex_lock(&pool.lock);
    if (!pool.shutdown) {
        if (!pool.tail)
            pool.head = pool.tail = t;
        else {
            pool.tail->next = t;
            pool.tail = t;
        }
        pthread_cond_signal(&pool.cond);
    } else {
        close(fd);
        free(t);
    }
    pthread_mutex_unlock(&pool.lock);
}

task_t* dequeue() {
    task_t *t = pool.head;
    if (!t) return NULL;
    pool.head = t->next;
    if (!pool.head) pool.tail = NULL;
    return t;
}

void* worker(void *arg) {
    (void)arg;
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

        char buf[BUFFER_SIZE];
        int n = recv(t->client_fd, buf, sizeof(buf), 0);
        if (n > 0)
            send(t->client_fd, buf, n, 0);

        close(t->client_fd);
        free(t);
    }
    return NULL;
}

void init_pool() {
    pthread_mutex_init(&pool.lock, NULL);
    pthread_cond_init(&pool.cond, NULL);
    pool.head = pool.tail = NULL;
    pool.shutdown = 0;

    for (int i = 0; i < WORKERS; i++)
        pthread_create(&pool.threads[i], NULL, worker, NULL);
}

void destroy_pool() {
    pthread_mutex_lock(&pool.lock);
    pool.shutdown = 1;
    pthread_cond_broadcast(&pool.cond);
    pthread_mutex_unlock(&pool.lock);

    for (int i = 0; i < WORKERS; i++)
        pthread_join(pool.threads[i], NULL);

    /* Free remaining queued tasks */
    task_t *t = pool.head;
    while (t) {
        task_t *next = t->next;
        close(t->client_fd);
        free(t);
        t = next;
    }

    pthread_mutex_destroy(&pool.lock);
    pthread_cond_destroy(&pool.cond);
}

/* ================= MAIN ================= */
int main() {
    signal(SIGINT, handle_sigint);
    init_pool();

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)
    };

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, BACKLOG);
    make_nonblocking(server_fd);

    int epfd = epoll_create1(0);
    struct epoll_event ev, events[MAX_EVENTS];

    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

    printf("🚀 Server running (Ctrl+C to shutdown)\n");

    while (running) {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, 1000);

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == server_fd) {
                while (1) {
                    int cfd = accept(server_fd, NULL, NULL);
                    if (cfd < 0) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK)
                            break;
                        continue;
                    }
                    make_nonblocking(cfd);
                    enqueue(cfd);
                }
            }
        }
    }

    printf("🛑 Shutdown initiated...\n");

    close(server_fd);
    close(epfd);
    destroy_pool();

    printf("✅ Shutdown complete\n");
    return 0;
}

