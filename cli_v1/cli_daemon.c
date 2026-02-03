#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>

#define PORT 5000
#define MAX_SESSIONS 10
#define BUF_SIZE 256
#define IDLE_TIMEOUT 300   /* seconds */
typedef struct {
    int used;
    int fd;
    int session_id;
    time_t last_activity;
    struct sockaddr_in addr;
} cli_session_t;

static cli_session_t sessions[MAX_SESSIONS];
static int next_session_id = 1;

void send_prompt(int fd)
{
    write(fd, "skdpp# ", 7);
}

void remove_session(int idx)
{
    close(sessions[idx].fd);
    sessions[idx].used = 0;
}

void check_session_timeouts(void)
{
    time_t now = time(NULL);

    for (int i = 0; i < MAX_SESSIONS; i++) 
    {
        if (sessions[i].used) 
	{
            if ((now - sessions[i].last_activity) > IDLE_TIMEOUT) 
	    {
                write(sessions[i].fd,
                      "\nSession timed out\n",
                      strlen("\nSession timed out\n"));
                remove_session(i);
            }
        }
    }
}

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
    const char *clr = "\033[2J\033[H";
    write(fd, clr, strlen(clr));
}

void cmd_show_sessions(int fd)
{
    char buf[256];

    write(fd, "\nSID   IP ADDRESS       FD\n", 27);

    for (int i = 0; i < MAX_SESSIONS; i++) 
    {
        if (sessions[i].used) 
	{
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

void process_command(int idx, char *cmd)
{
    int fd = sessions[idx].fd;

    if (!strcmp(cmd, "help") || !strcmp(cmd, "?")) {
        cmd_help(fd);
    }
    else if (!strcmp(cmd, "show sessions")) {
        cmd_show_sessions(fd);
    }
    else if (cmd[0] == 0x0c || !strcmp(cmd, "clear")) {
        cmd_clear(fd);
    }
    else if (!strcmp(cmd, "exit") || !strcmp(cmd, "logout")) {
        write(fd, "Bye\r\n", 4);
        remove_session(idx);
        return;
    }
    else if (strlen(cmd) == 0) {
        /* ignore empty input */
    }
    else {
        const char *err = "Unknown command (type 'help')\r\n";
        write(fd, err, strlen(err));
    }

    if (sessions[idx].used)
        send_prompt(fd);
}

int main(void)
{
    int listen_fd, maxfd;
    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) 
    {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("172.21.24.23"); //INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(listen_fd,
             (struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0) 
    {
        perror("bind");
        exit(1);
    }

    if (listen(listen_fd, 5) < 0) 
    {
        perror("listen");
        exit(1);
    }

    printf("CLI daemon listening on port %d\n", PORT);

    while (1) 
    {
        fd_set readfds;
        FD_ZERO(&readfds);

        FD_SET(listen_fd, &readfds);
        maxfd = listen_fd;

        for (int i = 0; i < MAX_SESSIONS; i++) 
	{
            if (sessions[i].used) 
	    {
                FD_SET(sessions[i].fd, &readfds);
                if (sessions[i].fd > maxfd)
                    maxfd = sessions[i].fd;
            }
        }

        struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

        if (select(maxfd + 1, &readfds,
                   NULL, NULL, &tv) < 0)
            continue;

        /* New connection */
        if (FD_ISSET(listen_fd, &readfds)) 
	{
            struct sockaddr_in cliaddr;
            socklen_t len = sizeof(cliaddr);
            int client_fd = accept(listen_fd,
                                   (struct sockaddr *)&cliaddr,
                                   &len);
            if (client_fd >= 0) 
	    {
                int added = 0;
                for (int i = 0; i < MAX_SESSIONS; i++) 
		{
                    if (!sessions[i].used) 
		    {
                        sessions[i].used = 1;
                        sessions[i].fd = client_fd;
                        sessions[i].addr = cliaddr;
                        sessions[i].session_id = next_session_id++;
                        sessions[i].last_activity = time(NULL);
                        const char *msg =
                            "\r\nWelcome to CLI\r\nType 'help' or '?' to know available commands\r\n";
                        write(client_fd, msg, strlen(msg));
                        send_prompt(client_fd);

                        added = 1;
                        break;
                    }
                }

                if (!added) 
		{
                    const char *full =
                        "Too many sessions\r\n";
                    write(client_fd, full, strlen(full));
                    close(client_fd);
                }
            }
        }

        /* Existing sessions */
        for (int i = 0; i < MAX_SESSIONS; i++) 
	{
            if (sessions[i].used &&
                FD_ISSET(sessions[i].fd, &readfds)) 
	    {
		char c;
		char buf[BUF_SIZE];
		int len = 0;
		while(1) {
                int n = read(sessions[i].fd,
                             &c, 1);
                if (n <= 0) 
		{
                    remove_session(i);
                    continue;
                }
		sessions[i].last_activity = time(NULL);
		if(c != '\n')
		{
			buf[len] = c;
			len++;
			continue;
		}
		buf[len] = '\0';
		break;
		}
                buf[strcspn(buf, "\r\n")] = '\0';

                process_command(i, buf);
            }
        }
	check_session_timeouts();
    }
}

