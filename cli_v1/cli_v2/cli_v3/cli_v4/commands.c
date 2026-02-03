#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "cli.h"
#include "session.h"

static void cmd_help(int fd)
{
    const char *help =
        "\r\nAvailable commands:\r\n"
        "  help or ?       - Show this help\r\n"
        "  show sessions   - Show active CLI sessions\r\n"
        "  clear           - Clear screen\r\n"
        "  exit | logout   - Close session\r\n"
        "  enable          - Switch to privilege mode[prompt changes to #]\r\n"
        "  disable         - Switch back to user mode[prompt changes to >]\r\n\r\n";
    write(fd, help, strlen(help));
}

static void cmd_clear(int fd)
{
    write(fd, "\033[2J\033[H", 7);
}

static void cmd_show_sessions(int fd)
{
    char buf[256];

    write(fd, "\r\nSID   IP ADDRESS       FD\r\n", 29);

    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sessions[i].used) {
            snprintf(buf, sizeof(buf),
                     "%-5d %-16s %d\r\n",
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

    if (!strcmp(cmd, "help") || !strcmp(cmd, "?"))
        cmd_help(fd);
    else if (!strcmp(cmd, "show sessions")) {
        if (sessions[idx].priv != PRIV_ADMIN) {
            write(fd, "Permission denied\r\n", 19);
        } else {
            cmd_show_sessions(fd);
        }
    }
    else if (cmd[0] == 0x0c || !strcmp(cmd, "clear"))
        cmd_clear(fd);
    else if (!strcmp(cmd, "exit") || !strcmp(cmd, "logout")) {
        write(fd, "Bye\r\n", 5);
        remove_session(idx);
        return;
    }
    else if (!strcmp(cmd, "enable")) {
        sessions[idx].priv = PRIV_ADMIN;
        write(fd, "Admin mode\r\n", 12);
    }
    else if (!strcmp(cmd, "disable")) {
        sessions[idx].priv = PRIV_USER;
        write(fd, "User mode\r\n", 11);
    }

    else if (*cmd) {
        write(fd, "Unknown command (type 'help')\r\n", 32);
    }

    if (sessions[idx].used)
        send_prompt(fd, sessions[idx].priv);
}

