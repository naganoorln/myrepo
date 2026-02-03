#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define PORT 9000
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

typedef void (*task_func)(void *arg);

typedef struct task {
    task_func func;
    void *arg;
    struct task *next;
} task_t;

typedef struct thread_pool {
    pthread_t *threads;
    int thread_count;

    task_t *head;
    task_t *tail;
    int task_count;

    pthread_mutex_t lock;
    pthread_cond_t notify;

    int shutdown;
} thread_pool_t;

typedef struct client_task {
    int client_fd;
} client_task_t;
void enqueue_task(thread_pool_t *pool, task_func func, void *arg) {
    task_t *task = malloc(sizeof(task_t));
    task->func = func;
    task->arg = arg;
    task->next = NULL;

    pthread_mutex_lock(&pool->lock);

    if (pool->tail == NULL) {
        pool->head = task;
        pool->tail = task;
    } else {
        pool->tail->next = task;
        pool->tail = task;
    }
    pool->task_count++;

    pthread_cond_signal(&pool->notify);
    pthread_mutex_unlock(&pool->lock);
}

task_t* dequeue_task(thread_pool_t *pool) {
    task_t *task = pool->head;
    if (task == NULL) return NULL;

    pool->head = task->next;
    if (pool->head == NULL) pool->tail = NULL;

    pool->task_count--;
    return task;
}

void* worker(void *arg) {
    thread_pool_t *pool = (thread_pool_t*)arg;

    while (1) {
        pthread_mutex_lock(&pool->lock);

        while (pool->task_count == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->notify, &pool->lock);
        }

        if (pool->shutdown && pool->task_count == 0) {
            pthread_mutex_unlock(&pool->lock);
            break;
        }

        task_t *task = dequeue_task(pool);
        pthread_mutex_unlock(&pool->lock);

        if (task) {
            task->func(task->arg);
            free(task);
        }
    }
    return NULL;
}

thread_pool_t* create_pool(int num_threads) {
    thread_pool_t *pool = malloc(sizeof(thread_pool_t));

    pool->thread_count = num_threads;
    pool->threads = malloc(sizeof(pthread_t) * num_threads);

    pool->head = NULL;
    pool->tail = NULL;
    pool->task_count = 0;
    pool->shutdown = 0;

    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->notify, NULL);

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&pool->threads[i], NULL, worker, pool);
    }

    return pool;
}

void shutdown_pool(thread_pool_t *pool) {
    pthread_mutex_lock(&pool->lock);
    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->notify);
    pthread_mutex_unlock(&pool->lock);

    for (int i = 0; i < pool->thread_count; i++) {
        pthread_join(pool->threads[i], NULL);
    }

    // Free pending tasks
    pthread_mutex_lock(&pool->lock);
    task_t *task = pool->head;
    while (task != NULL) {
        task_t *tmp = task;
        task = task->next;
        free(tmp->arg);
        free(tmp);
    }
    pthread_mutex_unlock(&pool->lock);

    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->notify);

    free(pool->threads);
    free(pool);
}


/* ====== Server Task ====== */
void handle_client(void *arg) {
    client_task_t *client = (client_task_t*)arg;
    int client_fd = client->client_fd;
    char buffer[BUFFER_SIZE];

    while (1) {
        int bytes = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) {
            printf("Client disconnected: %d\n", client_fd);
            break;
        }

        buffer[bytes] = '\0';
        printf("Received from %d: %s\n", client_fd, buffer);

        send(client_fd, buffer, bytes, 0);
    }

    close(client_fd);
    free(client);
}


/* ====== Signal Shutdown ====== */
volatile sig_atomic_t server_running = 1;

void sigint_handler(int signum) {
    server_running = 0;
}


/* ====== Main Server ====== */
int main() {
    //signal(SIGINT, sigint_handler);

    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    thread_pool_t *pool = create_pool(4);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, MAX_CLIENTS);
   
    /* Make non-blocking */
    int flags = fcntl(server_fd, F_GETFL, 0);
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);
    printf("Server running. Press Ctrl+C to stop.\n");
    printf("Server listening on port %d\n", PORT);

    while (server_running) {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            if (!server_running) break; // stop accepted when ctrl+c
            //perror("accept failed");
            continue;
        }

        client_task_t *client_task = malloc(sizeof(client_task_t));
        client_task->client_fd = client_fd;

        enqueue_task(pool, handle_client, client_task);
    }

    printf("Shutdown initiated...\n");
    shutdown_pool(pool);
    close(server_fd);
    printf("Server stopped\n");

    return 0;
}

