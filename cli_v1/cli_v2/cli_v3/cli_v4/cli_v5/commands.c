#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "cli.h"
#include "session.h"

static void cmd_help(cli_session_t *sess)
{
    const char *help =
        "\r\nAvailable commands:\r\n"
        "  help or ?       - Show this help\r\n"
        "  show sessions   - Show active CLI sessions\r\n"
        "  clear           - Clear screen\r\n"
        "  exit | logout   - Close session\r\n"
        "  enable          - Enter admin mode\r\n"
        "  disable         - Exit admin mode\r\n\r\n";
    session_write(sess, help, strlen(help));
}

static void cmd_clear(cli_session_t *sess)
{
    session_write(sess, "\033[2J\033[H", 7);
}

static void cmd_show_sessions(cli_session_t *sess)
{
    char buf[128];
    session_write(sess, "\r\nSID   IP ADDRESS       FD\r\n", 29);
    for(int i=0;i<MAX_SESSIONS;i++){
        if(sessions[i].used){
            snprintf(buf,sizeof(buf),"%-5d %-16s %d\r\n",
                     sessions[i].session_id,
                     inet_ntoa(sessions[i].addr.sin_addr),
                     (sessions[i].type==SESSION_TELNET)?sessions[i].fd:0);
            session_write(sess, buf, strlen(buf));
        }
    }
}

void process_command(int idx, char *cmd)
{
    cli_session_t *sess = &sessions[idx];

    if(!strcmp(cmd,"help") || !strcmp(cmd,"?"))
        cmd_help(sess);
    else if(!strcmp(cmd,"show sessions")){
        if(sess->priv != PRIV_ADMIN)
            session_write(sess,"Permission denied\r\n",19);
        else
            cmd_show_sessions(sess);
    }
    else if(!strcmp(cmd,"clear") || cmd[0]==0x0c)
        cmd_clear(sess);
    else if(!strcmp(cmd,"exit") || !strcmp(cmd,"logout")){
        session_write(sess,"Bye\r\n",5);
        remove_session(idx);
        return;
    }
    else if(!strcmp(cmd,"enable")){
        sess->priv = PRIV_ADMIN;
        session_write(sess,"Admin mode\r\n",12);
    }
    else if(!strcmp(cmd,"disable")){
        sess->priv = PRIV_USER;
        session_write(sess,"User mode\r\n",11);
    }
    else if(*cmd)
        session_write(sess,"Unknown command (type 'help')\r\n",32);

    if(sess->used)
        send_prompt(sess);
}

