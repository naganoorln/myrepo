#ifndef CLI_H
#define CLI_H

#include <netinet/in.h>
#include <time.h>

#define PORT 5000
#define MAX_SESSIONS 10
#define BUF_SIZE 256
#define IDLE_TIMEOUT 300

typedef struct {
    int used;
    int fd;
    int session_id;
    time_t last_activity;
    struct sockaddr_in addr;
} cli_session_t;

extern cli_session_t sessions[MAX_SESSIONS];

#endif

