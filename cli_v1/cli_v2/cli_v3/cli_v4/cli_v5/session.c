#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "session.h"

cli_session_t sessions[MAX_SESSIONS];

void remove_session(int idx)
{
    if(sessions[idx].type == SESSION_TELNET) {
        close(sessions[idx].fd);
    } else if(sessions[idx].type == SESSION_SSH) {
        if(sessions[idx].ssh_chan) ssh_channel_close(sessions[idx].ssh_chan);
        if(sessions[idx].ssh_chan) ssh_channel_free(sessions[idx].ssh_chan);
        if(sessions[idx].ssh_sess) ssh_disconnect(sessions[idx].ssh_sess);
        if(sessions[idx].ssh_sess) ssh_free(sessions[idx].ssh_sess);
    }
    sessions[idx].used = 0;
}

void check_session_timeouts(void)
{
    time_t now = time(NULL);

    for(int i=0; i<MAX_SESSIONS; i++) {
        if(sessions[i].used && (now - sessions[i].last_activity) > IDLE_TIMEOUT) {
            session_write(&sessions[i], "\r\nSession timed out\r\n", 23);
            remove_session(i);
        }
    }
}

int session_write(cli_session_t *sess, const char *buf, int len)
{
    if(sess->type == SESSION_TELNET)
        return write(sess->fd, buf, len);
    else if(sess->type == SESSION_SSH)
        return ssh_channel_write(sess->ssh_chan, buf, len);
    return -1;
}

void send_prompt(cli_session_t *sess)
{
    if(sess->priv == PRIV_ADMIN)
        session_write(sess, "skdpp# ", 7);
    else
        session_write(sess, "skdpp> ", 7);
}

