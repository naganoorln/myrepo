#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "fwnf_rule.h"

#define DEV "/dev/myfw"

static void banner(void)
{
    puts("========================================");
    puts("Simple Firewall CLI (Demo)        ");
    puts("========================================");
}

static void help(void)
{
    puts("\nConfiguration Commands");
    puts(" add sourceip <ip> destip <ip> port <port> action <accept|drop>");
    puts(" del <index>");
    puts(" clear");

    puts("\nShow Commands");
    puts(" list");
    puts(" show running-config");

    puts("\nSystem Commands");
    puts(" cls");
    puts(" help");
    puts(" exit\n");
}

static void list_rules(int fd)
{
    struct fw_rule_list list;
    struct in_addr ip;
    int i;

    if (ioctl(fd, FW_IOCTL_LIST_RULES, &list) < 0)
        return;

    if (list.count == 0) {
        puts("\nNo rules configured\n");
        return;
    }

    puts("\nIdx  Source IP        Destination IP   Port  Action");
    puts("-----------------------------------------------------");

    for (i = 0; i < list.count; i++) {
        ip.s_addr = list.rules[i].src_ip;
        printf("%-4d %-16s ", i, inet_ntoa(ip));
        ip.s_addr = list.rules[i].dst_ip;
        printf("%-16s %-5u %s\n",
               inet_ntoa(ip),
               list.rules[i].dst_port,
               list.rules[i].action ? "ACCEPT" : "DROP");
    }
}

static void show_running_config(int fd)
{
    struct fw_rule_list list;
    struct in_addr ip;
    int i;

    if (ioctl(fd, FW_IOCTL_LIST_RULES, &list) < 0)
        return;

    if (list.count == 0) {
        puts("\nNo firewall rules configured\n");
        return;
    }

    puts("\n========================================");
    puts("        FIREWALL RUNNING CONFIG");
    puts("========================================\n");

    puts("firewall enable\n");

    for (i = 0; i < list.count; i++) {
        printf("rule %d\n", i);

        ip.s_addr = list.rules[i].src_ip;
        printf(" sourceip %s\n", inet_ntoa(ip));

        ip.s_addr = list.rules[i].dst_ip;
        printf(" destip   %s\n", inet_ntoa(ip));

        printf(" port     %u\n", list.rules[i].dst_port);
        printf(" action   %s\n\n",
               list.rules[i].action ? "accept" : "drop");
    }

    puts("end");
    puts("========================================");
}

static int parse_add(char *line, struct fw_rule *r)
{
    char *tok;
    int s=0,d=0,p=0,a=0;

    memset(r, 0, sizeof(*r));
    strtok(line, " ");

    while ((tok = strtok(NULL, " "))) {
        if (!strcmp(tok, "sourceip")) {
            r->src_ip = inet_addr(strtok(NULL, " "));
            s = 1;
        } else if (!strcmp(tok, "destip")) {
            r->dst_ip = inet_addr(strtok(NULL, " "));
            d = 1;
        } else if (!strcmp(tok, "port")) {
            r->dst_port = atoi(strtok(NULL, " "));
            p = 1;
        } else if (!strcmp(tok, "action")) {
            tok = strtok(NULL, " ");
            r->action = !strcmp(tok, "accept");
            a = 1;
        }
    }
    return s && d && p && a ? 0 : -1;
}

int main(void)
{
    int fd = open(DEV, O_RDWR);
    char line[256], tmp[256];

    if (fd < 0) {
        perror("open");
        return 1;
    }

    banner();
    help();

    while (1) {
        printf("fw> ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;

        if (!strcmp(line, "exit")) break;
        if (!strcmp(line, "help")) help();
        else if (!strcmp(line, "cls")) system("clear");
        else if (!strcmp(line, "list")) list_rules(fd);
        else if (!strcmp(line, "show running-config")) show_running_config(fd);
        else if (!strcmp(line, "clear")) ioctl(fd, FW_IOCTL_CLEAR_RULE);
        else if (!strncmp(line, "del ", 4)) {
            int idx = atoi(line + 4);
            ioctl(fd, FW_IOCTL_DEL_RULE, &idx);
        }
        else if (!strncmp(line, "add ", 4)) {
            struct fw_rule r;
            strcpy(tmp, line);
            if (parse_add(tmp, &r) == 0)
                ioctl(fd, FW_IOCTL_ADD_RULE, &r);
            else
                puts("Invalid add command (type help)");
        }
        else
            puts("Unknown command (type help)");
    }

    close(fd);
    return 0;
}

