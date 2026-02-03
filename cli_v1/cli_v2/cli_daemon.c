#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>

/* ================= CONFIG ================= */

#define PORT 5000
#define MAX_SESSIONS 10
#define BUF_SIZE 256
#define IDLE_TIMEOUT 300   /* seconds */

/* ================= SESSION ================= */

typedef struct {
    int used;
    int fd;
    int session_id;
    time_t last_activity;
    struct sockaddr_in addr;
} cli_session_t;

static cli_session_t sessions[MAX_SESSIONS];
static int next_session_id = 1;

/* ================= PROMPT ================= */

void send_prompt(int fd)
{
    write(fd, "skdpp# ", 7);
}

/* ================= SESSION MANAGEMENT ================= */

void remove_session(int idx)
{
    close(sessions[idx].fd);
    sessions[idx].used = 0;
}

void check_session_timeouts(void)
{
    time_t now = time(NULL);

    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sessions[i].used &&
            (now - sessions[i].last_activity) > IDLE_TIMEOUT) {

            write(sessions[i].fd,
                  "\nSession timed out\n",
                  20);
            remove_session(i);
        }
    }
}

int add_session(int client_fd, struct sockaddr_in *addr)
{
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (!sessions[i].used) {
            sessions[i].used = 1;
            sessions[i].fd = client_fd;
            sessions[i].addr = *addr;
            sessions[i].session_id = next_session_id++;
            sessions[i].last_activity = time(NULL);

            write(client_fd,
                  "\r\nWelcome to CLI\r\n"
                  "Type 'help' or '?' to know available commands\r\n",
                  66);
            send_prompt(client_fd);
            return 0;
        }
    }
    return -1;
}

/* ================= COMMANDS ================= */

void cmd_help(int fd)
{
    const char *help =
        "\r\nAvailable commands:\r\n"
        "  help or ?       - Show this help\r\n"
        "  show sessions   - Show active CLI sessions\r\n"
        "  clear           - Clear screen\r\n"
        "  exit | logout   - Close session\r\n\r\n";
    write(fd, help, strlen(help));
}

void cmd_clear(int fd)
{
    write(fd, "\033[2J\033[H", 7);
}

void cmd_show_sessions(int fd)
{
    char buf[128];
    write(fd, "\nSID   IP ADDRESS       FD\n", 27);

    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sessions[i].used) {
            snprintf(buf, sizeof(buf),
                     "\r%-5d %-16s %d\n",
                     sessions[i].session_id,
                     inet_ntoa(sessions[i].addr.sin_addr),
                     sessions[i].fd);
            write(fd, buf, strlen(buf));
        }
    }
    write(fd, "\r\n", 1);
}

/* ================= COMMAND DISPATCH ================= */

void process_command(int idx, char *cmd)
{
    int fd = sessions[idx].fd;

    if (!strcmp(cmd, "help") || !strcmp(cmd, "?"))
        cmd_help(fd);
    else if (!strcmp(cmd, "show sessions"))
        cmd_show_sessions(fd);
    else if (!strcmp(cmd, "clear") || cmd[0] == 0x0c)
        cmd_clear(fd);
    else if (!strcmp(cmd, "exit") || !strcmp(cmd, "logout")) {
        write(fd, "Bye\r\n", 5);
        remove_session(idx);
        return;
    }
    else if (*cmd)
        write(fd, "Unknown command (type 'help')\r\n", 32);

    if (sessions[idx].used)
        send_prompt(fd);
}

/* ================= INPUT HANDLING ================= */

void handle_session_input(int idx)
{
    char c, buf[BUF_SIZE];
    int len = 0;

    while (1) {
        int n = read(sessions[idx].fd, &c, 1);
        if (n <= 0) {
            remove_session(idx);
            return;
        }

        sessions[idx].last_activity = time(NULL);

        if (c == '\r')
            continue;

        if (c == '\n')
            break;

        if (len < BUF_SIZE - 1)
            buf[len++] = c;
    }

    buf[len] = '\0';
    process_command(idx, buf);
}

/* ================= SERVER ================= */

int main(void)
{
    int listen_fd, maxfd;
    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("172.21.24.23");
    servaddr.sin_port = htons(PORT);

    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listen_fd, 5);

    printf("CLI daemon listening on port %d\n", PORT);

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

        /* Accept new connection */
        if (FD_ISSET(listen_fd, &readfds)) {
            struct sockaddr_in cliaddr;
            socklen_t len = sizeof(cliaddr);
            int fd = accept(listen_fd,
                            (struct sockaddr *)&cliaddr,
                            &len);
            if (add_session(fd, &cliaddr) < 0) {
                write(fd, "Too many sessions\r\n", 19);
                close(fd);
            }
        }

        /* Existing sessions */
        for (int i = 0; i < MAX_SESSIONS; i++) {
            if (sessions[i].used &&
                FD_ISSET(sessions[i].fd, &readfds)) {
                handle_session_input(i);
            }
        }

        check_session_timeouts();
    }
}

