#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "acl_mgr.h"

void cli_process(char *line)
{
    char ip[32], action[16];
    acl_rule_t rule;

    if (sscanf(line, "acl add src-ip %31s %15s",
               ip, action) != 2) {
        printf("Invalid command\n");
        return;
    }

    rule.src_ip = ntohl(inet_addr(ip));
    rule.src_mask = 0xFFFFFFFF;
    rule.action = (!strcmp(action, "drop")) ?
                    ACL_ACTION_DROP :
                    ACL_ACTION_PERMIT;

    acl_mgr_add_rule(&rule);
    printf("ACL installed\n");
}

