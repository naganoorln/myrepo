#ifndef SESSION_H
#define SESSION_H

#include "cli.h"

void remove_session(int idx);
void check_session_timeouts(void);
void send_prompt(int fd);

#endif

