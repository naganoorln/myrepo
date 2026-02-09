#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/fib_rules.h>
#include <net/if.h>

#define BUFSIZE 8192

int sock;

void print_help(void)
{
    printf(
        "\nAvailable commands:\n"
        "  help or ?		Show this help\n"
	"  clear|clr|Ctrl+L	Clear Console\n"
        "  ip link show        	Show interfaces\n"
        "  ip addr show        	Show IP addresses\n"
        "  ip route show       	Show routing table\n"
        "  ip neigh show       	Show ARP table\n"
        "  ip rule show        	Show routing rules\n"
        "  exit | quit         	Exit CLI\n\n"
    );
}

void request_send(int type, int family)
{
    char buf[BUFSIZE];
    memset(buf, 0, sizeof(buf));

    struct nlmsghdr *nlh = (struct nlmsghdr *)buf;
    struct rtmsg *rtm = (struct rtmsg *)NLMSG_DATA(nlh);

    nlh->nlmsg_len   = NLMSG_LENGTH(sizeof(*rtm));
    nlh->nlmsg_type  = type;
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    nlh->nlmsg_seq   = 1;
    nlh->nlmsg_pid   = getpid();

    rtm->rtm_family = family;

    struct sockaddr_nl kernel = {
        .nl_family = AF_NETLINK
    };

    sendto(sock, nlh, nlh->nlmsg_len, 0,
           (struct sockaddr *)&kernel, sizeof(kernel));
}

void reply_recv(void)
{
    char buf[BUFSIZE];
    int len;

    while ((len = recv(sock, buf, sizeof(buf), 0)) > 0) {
        struct nlmsghdr *nlh;

        for (nlh = (struct nlmsghdr *)buf;
             NLMSG_OK(nlh, len);
             nlh = NLMSG_NEXT(nlh, len)) {

            if (nlh->nlmsg_type == NLMSG_DONE)
                return;

            if (nlh->nlmsg_type == NLMSG_ERROR)
                return;

            /* Routes */
            if (nlh->nlmsg_type == RTM_NEWROUTE) {
                struct rtmsg *rtm = NLMSG_DATA(nlh);
                struct rtattr *attr = RTM_RTA(rtm);
                int alen = RTM_PAYLOAD(nlh);

                char dst[INET_ADDRSTRLEN] = "default";
                char gw[INET_ADDRSTRLEN] = "";
                int oif = 0;

                for (; RTA_OK(attr, alen); attr = RTA_NEXT(attr, alen)) {
                    if (attr->rta_type == RTA_DST)
                        inet_ntop(AF_INET, RTA_DATA(attr), dst, sizeof(dst));
                    else if (attr->rta_type == RTA_GATEWAY)
                        inet_ntop(AF_INET, RTA_DATA(attr), gw, sizeof(gw));
                    else if (attr->rta_type == RTA_OIF)
                        oif = *(int *)RTA_DATA(attr);
                }
                printf("dst=%s gw=%s oif=%d\n", dst, gw, oif);
            }

            /* Arp */
            else if (nlh->nlmsg_type == RTM_NEWNEIGH) {
                struct ndmsg *ndm = (struct ndmsg *)NLMSG_DATA(nlh);

                struct rtattr *attr =
                (struct rtattr *)((char *)ndm + NLMSG_ALIGN(sizeof(*ndm)));

                int alen = nlh->nlmsg_len - NLMSG_LENGTH(sizeof(*ndm));
                char ip[INET_ADDRSTRLEN] = "";
                unsigned char *mac = NULL;

                for (; RTA_OK(attr, alen); attr = RTA_NEXT(attr, alen)) {
                    if (attr->rta_type == NDA_DST)
                        inet_ntop(AF_INET, RTA_DATA(attr), ip, sizeof(ip));
                    else if (attr->rta_type == NDA_LLADDR)
                        mac = RTA_DATA(attr);
                }

                if (mac)
                    printf("%s lladdr %02x:%02x:%02x:%02x:%02x:%02x\n",
                           ip, mac[0], mac[1], mac[2],
                           mac[3], mac[4], mac[5]);
            }

            /* Link */
            else if (nlh->nlmsg_type == RTM_NEWLINK) {
                struct ifinfomsg *ifi = NLMSG_DATA(nlh);
                printf("ifindex=%d flags=0x%x\n",
                       ifi->ifi_index, ifi->ifi_flags);
            }

            /* Ip Address */
            else if (nlh->nlmsg_type == RTM_NEWADDR) {
                struct ifaddrmsg *ifa = NLMSG_DATA(nlh);
                struct rtattr *attr = IFA_RTA(ifa);
                int alen = IFA_PAYLOAD(nlh);
                char ip[INET_ADDRSTRLEN] = "";

                for (; RTA_OK(attr, alen); attr = RTA_NEXT(attr, alen))
                    if (attr->rta_type == IFA_LOCAL)
                        inet_ntop(AF_INET, RTA_DATA(attr), ip, sizeof(ip));

                if (ip[0])
                    printf("%s ifindex=%d\n", ip, ifa->ifa_index);
            }
	    /* Rules */
	    else if (nlh->nlmsg_type == RTM_NEWRULE) {
    		struct fib_rule_hdr *frh = NLMSG_DATA(nlh);
                struct rtattr *attr = (struct rtattr *)((char *)frh + NLMSG_ALIGN(sizeof(*frh)));
		int alen = nlh->nlmsg_len - NLMSG_LENGTH(sizeof(*frh));

    		int priority = -1;
    		int table = frh->table;
    		char src[INET_ADDRSTRLEN] = "all";
    		char dst[INET_ADDRSTRLEN] = "all";
    		char iif[IFNAMSIZ] = "";
    		char oif[IFNAMSIZ] = "";

    	   	for (; RTA_OK(attr, alen); attr = RTA_NEXT(attr, alen)) {
       		    switch (attr->rta_type) {
        	    case FRA_PRIORITY:
            		priority = *(int *)RTA_DATA(attr);
            		break;
        	    case FRA_TABLE:
            		table = *(int *)RTA_DATA(attr);
            		break;
        	    case FRA_SRC:
            		inet_ntop(AF_INET, RTA_DATA(attr), src, sizeof(src));
            		break;
        	    case FRA_DST:
            		inet_ntop(AF_INET, RTA_DATA(attr), dst, sizeof(dst));
            		break;
        	    case FRA_IIFNAME:
            		strncpy(iif, RTA_DATA(attr), IFNAMSIZ);
            		break;
        	    case FRA_OIFNAME:
            		strncpy(oif, RTA_DATA(attr), IFNAMSIZ);
            		break;
        	    }
    	        }  

    	        printf("rule: prio=%d table=%d src=%s dst=%s",
           	       priority, table, src, dst);

    	        if (iif[0]) printf(" iif=%s", iif);
                if (oif[0]) printf(" oif=%s", oif);
                printf("\n");
	    }

        }
    }
}

int main(void)
{
    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

    struct sockaddr_nl local = {
        .nl_family = AF_NETLINK,
        .nl_pid = getpid()
    };
    bind(sock, (struct sockaddr *)&local, sizeof(local));

    char line[128];

    printf("Netlink CLI\nType 'help' for commands\n\n");

    while (1) {
        printf("netlink> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;

        line[strcspn(line, "\n")] = 0;

        if (!strcmp(line, "exit") || !strcmp(line, "quit"))
            break;

        if (!strcmp(line, "help") || !strcmp(line, "?")) {
            print_help();
            continue;
        }

        if (strcmp(line, "clear") == 0 || strcmp(line, "clr") == 0 || line[0] == 0x0c) {
            printf("\033[2J\033[H");
	    continue;
        }

        if (!strcmp(line, "ip route show")) {
            request_send(RTM_GETROUTE, AF_INET);
            reply_recv();
        }
        else if (!strcmp(line, "ip neigh show")) {
            request_send(RTM_GETNEIGH, AF_INET);
            reply_recv();
        }
        else if (!strcmp(line, "ip link show")) {
            request_send(RTM_GETLINK, AF_PACKET);
            reply_recv();
        }
        else if (!strcmp(line, "ip addr show")) {
            request_send(RTM_GETADDR, AF_INET);
            reply_recv();
        }
        else if (!strcmp(line, "ip rule show")) {
            request_send(RTM_GETRULE, AF_INET);
            reply_recv();
        }
        else {
            printf("Unknown command. Type 'help'\n");
        }
    }

    close(sock);
    return 0;
}

