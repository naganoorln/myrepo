#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "acl_mgr.h"

void cli_process(char *line)
{
    char cmd[16], subcmd[16], src_kw[16], ip_str[32], action[16];
    acl_rule_t rule;

    /* Parse command */
    if (sscanf(line, "%15s %15s %15s %31s %15s",
               cmd, subcmd, src_kw, ip_str, action) != 5) {
        printf("Invalid command\n");
        return;
    }

    if (strcmp(cmd, "acl") || strcmp(subcmd, "add") ||
        strcmp(src_kw, "src-ip")) {
        printf("Unknown command\n");
        return;
    }

    rule.src_ip = ntohl(inet_addr(ip_str));
    rule.src_mask = 0xFFFFFFFF;

    if (!strcmp(action, "drop"))
        rule.action = ACL_ACTION_DROP;
    else
        rule.action = ACL_ACTION_PERMIT;

    if (acl_mgr_add_rule(&rule) == 0)
        printf("ACL rule installed\n");
    else
        printf("ACL rule failed\n");
}

