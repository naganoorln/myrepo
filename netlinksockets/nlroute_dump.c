#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
int main(void)
{
    int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_nl local = {
        .nl_family = AF_NETLINK,
        .nl_pid = getpid(),
    };

    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    struct nlmsghdr *nlh = (struct nlmsghdr *)buffer;
    struct rtmsg *rtm = (struct rtmsg *)NLMSG_DATA(nlh);

    nlh->nlmsg_len = NLMSG_LENGTH(sizeof(*rtm));
    nlh->nlmsg_type = RTM_GETROUTE;
    nlh->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST;
    nlh->nlmsg_seq = 1;
    nlh->nlmsg_pid = getpid();

    rtm->rtm_family = AF_INET;   
    rtm->rtm_table  = RT_TABLE_MAIN;
    struct sockaddr_nl kernel = {
    	 .nl_family = AF_NETLINK,
    };

    if (sendto(sock, nlh, nlh->nlmsg_len, 0,
       	   (struct sockaddr *)&kernel, sizeof(kernel)) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
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

             struct rtmsg *rtm = (struct rtmsg *)NLMSG_DATA(nlh);
             struct rtattr *attr = RTM_RTA(rtm);
             int attrlen = RTM_PAYLOAD(nlh);
        
             char dst[INET_ADDRSTRLEN] = "default";
             char gw[INET_ADDRSTRLEN] = "";
             int oif = 0;

             for (; RTA_OK(attr, attrlen); attr = RTA_NEXT(attr, attrlen)) {
            	 switch (attr->rta_type) {
            	 case RTA_DST:
                     inet_ntop(AF_INET, RTA_DATA(attr), dst, sizeof(dst));
                     break;
        	 case RTA_GATEWAY:
                     inet_ntop(AF_INET, RTA_DATA(attr), gw, sizeof(gw));
                     break;
            	 case RTA_OIF:
                     oif = *(int *)RTA_DATA(attr);
                     break;
            	 }
            }

        	    printf("dst=%s gw=%s oif=%d\n", dst, gw, oif);
    	}
    }

    done:
    close(sock);
}

