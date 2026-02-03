#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include "cli.h"
#include "session.h"
#include "commands.h"

static int next_session_id = 1;

void server_loop(int listen_fd)
{
    int maxfd;

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);

        FD_SET(listen_fd, &readfds);
        maxfd = listen_fd;

        for (int i = 0; i < MAX_SESSIONS; i++) {
            if (sessions[i].used) {
                FD_SET(sessions[i].fd, &readfds);
                if (sessions[i].fd > maxfd)
                    maxfd = sessions[i].fd;
            }
        }

        struct timeval tv = {1, 0};
        select(maxfd + 1, &readfds, NULL, NULL, &tv);

        if (FD_ISSET(listen_fd, &readfds)) {
            struct sockaddr_in cliaddr;
            socklen_t len = sizeof(cliaddr);
            int fd = accept(listen_fd,
                            (struct sockaddr *)&cliaddr, &len);

            if (fd >= 0) {
                for (int i = 0; i < MAX_SESSIONS; i++) {
                    if (!sessions[i].used) {
                        sessions[i].used = 1;
                        sessions[i].fd = fd;
                        sessions[i].addr = cliaddr;
                        sessions[i].session_id = next_session_id++;
                        sessions[i].last_activity = time(NULL);
                        sessions[i].priv = PRIV_USER;

                        write(fd,
                              "\r\nWelcome to CLI\r\nType 'help'\r\n",
                              32);
                        send_prompt(fd, sessions[i].priv);
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < MAX_SESSIONS; i++) {
            if (sessions[i].used &&
                FD_ISSET(sessions[i].fd, &readfds)) {

                char c, buf[BUF_SIZE];
                int len = 0;

                while (read(sessions[i].fd, &c, 1) > 0) {
                    sessions[i].last_activity = time(NULL);
                    if (c == '\n') break;
                    if (len < BUF_SIZE - 1)
                        buf[len++] = c;
                }

                buf[len] = 0;
                buf[strcspn(buf, "\r\n")] = 0;
                process_command(i, buf);
            }
        }

        check_session_timeouts();
    }
}

