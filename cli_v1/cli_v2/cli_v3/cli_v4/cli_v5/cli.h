#ifndef CLI_H
#define CLI_H

#include <netinet/in.h>
#include <time.h>
#include <libssh/libssh.h>
#include <libssh/server.h>

/* Configuration */
#define PORT 5000
#define MAX_SESSIONS 10
#define BUF_SIZE 256
#define IDLE_TIMEOUT 300
#define CMD_BUF_SIZE 256

/* Privilege */
typedef enum {
    PRIV_USER = 0,
    PRIV_ADMIN = 1
} privilege_t;

/* Session type */
typedef enum {
    SESSION_TELNET = 0,
    SESSION_SSH = 1
} session_type_t;

/* CLI session */
typedef struct {
    int used;
    int fd;                  /* Telnet only */
    ssh_session ssh_sess;    /* SSH only */
    ssh_channel ssh_chan;    /* SSH channel */
    int session_id;
    time_t last_activity;
    struct sockaddr_in addr;
    privilege_t priv;
    session_type_t type;
    /* command buffer (for Telnet + SSH) */
    char cmd_buf[CMD_BUF_SIZE];
    int  cmd_len;
} cli_session_t;

extern cli_session_t sessions[MAX_SESSIONS];

#endif

