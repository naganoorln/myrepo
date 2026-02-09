#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h>

#define BUFSIZE 8192

int main(void)
{
    int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_nl local;
    memset(&local, 0, sizeof(local));
    local.nl_family = AF_NETLINK;
    local.nl_pid = getpid();

    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0) {
        perror("bind");
        return 1;
    }

    char buffer[BUFSIZE];
    memset(buffer, 0, sizeof(buffer));

    struct nlmsghdr *nlh = (struct nlmsghdr *)buffer;
    struct ndmsg *ndm = (struct ndmsg *)NLMSG_DATA(nlh);

    nlh->nlmsg_len   = NLMSG_LENGTH(sizeof(*ndm));
    nlh->nlmsg_type  = RTM_GETNEIGH;
    nlh->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST;
    nlh->nlmsg_seq   = 1;
    nlh->nlmsg_pid   = getpid();

    ndm->ndm_family = AF_INET;  

    struct sockaddr_nl kernel;
    memset(&kernel, 0, sizeof(kernel));
    kernel.nl_family = AF_NETLINK;

    if (sendto(sock, nlh, nlh->nlmsg_len, 0,
               (struct sockaddr *)&kernel, sizeof(kernel)) < 0) {
        perror("sendto");
        return 1;
    }

    int len;
    while ((len = recv(sock, buffer, sizeof(buffer), 0)) > 0) {

        for (nlh = (struct nlmsghdr *)buffer;
             NLMSG_OK(nlh, len);
             nlh = NLMSG_NEXT(nlh, len)) {

            if (nlh->nlmsg_type == NLMSG_DONE)
                goto done;

            if (nlh->nlmsg_type == NLMSG_ERROR) {
                fprintf(stderr, "Netlink error\n");
                goto done;
            }

            if (nlh->nlmsg_type != RTM_NEWNEIGH)
                continue;

            struct ndmsg *ndm = (struct ndmsg *)NLMSG_DATA(nlh);

            struct rtattr *attr =
            (struct rtattr *)((char *)ndm + NLMSG_ALIGN(sizeof(*ndm)));

            int attrlen = nlh->nlmsg_len - NLMSG_LENGTH(sizeof(*ndm));

            char ip[INET_ADDRSTRLEN] = "";
            char mac[32] = "";
            char ifname[IF_NAMESIZE] = "";

            for (; RTA_OK(attr, attrlen); attr = RTA_NEXT(attr, attrlen)) {

                switch (attr->rta_type) {

                case NDA_DST:
                    inet_ntop(AF_INET, RTA_DATA(attr),
                              ip, sizeof(ip));
                    break;

                case NDA_LLADDR: {
                    unsigned char *m = RTA_DATA(attr);
                    snprintf(mac, sizeof(mac),
                             "%02x:%02x:%02x:%02x:%02x:%02x",
                             m[0], m[1], m[2], m[3], m[4], m[5]);
                    break;
                }

                case NDA_IFINDEX:
                    if_indextoname(*(int *)RTA_DATA(attr), ifname);
                    break;
                }
            }

            if (ip[0] != '\0') {
                printf("ip=%-15s mac=%-17s dev=%s state=0x%x\n",
                       ip,
                       mac[0] ? mac : "incomplete",
                       ifname,
                       ndm->ndm_state);
            }
        }
    }

done:
    close(sock);
    return 0;
}

