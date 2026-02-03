#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "server.h"
#include "cli.h"

int main(void)
{
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    setsockopt(listen_fd, SOL_SOCKET,
               SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(listen_fd, 5);

    printf("CLI daemon listening on port %d\n", PORT);
    server_loop(listen_fd);
}

