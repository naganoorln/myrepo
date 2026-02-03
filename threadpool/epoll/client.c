#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define CLIENTS 100000

void *client_task(void *arg) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return NULL; }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = inet_addr(SERVER_IP)
    };

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(fd);
        return NULL;
    }

    // Send request
    const char *msg = "Hello from client\n";
    write(fd, msg, strlen(msg));

    // Optional: read response
    char buf[1024];
    int n = read(fd, buf, sizeof(buf) - 1);
    if (n > 0) {
        buf[n] = 0;
        printf("Received: %s", buf);
    }

    // Keep connection open if needed
    // sleep(10); 

    close(fd);
    return NULL;
}

int main() {
    pthread_t threads[CLIENTS];

    for (int i = 0; i < CLIENTS; i++) {
        if (pthread_create(&threads[i], NULL, client_task, NULL) != 0) {
            perror("pthread_create");
        }
    }

    for (int i = 0; i < CLIENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

