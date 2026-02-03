#include <unistd.h>
#include <string.h>
#include <time.h>
#include "session.h"

cli_session_t sessions[MAX_SESSIONS];

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

    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sessions[i].used &&
            (now - sessions[i].last_activity) > IDLE_TIMEOUT) {

            write(sessions[i].fd,
                  "\r\nSession timed out\r\n",
                  22);
            remove_session(i);
        }
    }
}

