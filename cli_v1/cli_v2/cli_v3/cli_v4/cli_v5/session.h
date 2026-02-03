#ifndef SESSION_H
#define SESSION_H

#include "cli.h"

void remove_session(int idx);
void check_session_timeouts(void);
int session_write(cli_session_t *sess, const char *buf, int len);
void send_prompt(cli_session_t *sess);

#endif

