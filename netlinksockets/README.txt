Netlink Socket Programming – Basic Model (Step-by-Step)

1. What is Netlink?
Netlink is a socket-based IPC mechanism used for communication between:

User space programs

Linux kernel networking subsystem

It replaces many /proc and ioctl interfaces.

Examples of what Netlink is used for:

Routing table (ip route)

Interfaces (ip link)

IP addresses (ip addr)

ARP / neighbor table (ip neigh)

Policy routing rules (ip rule)


2. High-Level Netlink Communication Model
+------------------+           +---------------------+
| User Application |  <---->   | Linux Kernel        |
| (AF_NETLINK)     |           | (NETLINK_ROUTE)    |
+------------------+           +---------------------+


Communication is:

Message-based

Attribute-based

Asynchronous


3. Basic Steps in Any Netlink Program

Every Netlink socket program follows the same 6 steps.

Step 1: Create Netlink Socket
int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

Explanation

Field		Meaning
AF_NETLINK	Address family for kernel communication
SOCK_RAW	Raw Netlink messages
NETLINK_ROUTE	Routing & link subsystem

Example mapping:

ip route show  →  NETLINK_ROUTE + RTM_GETROUTE

Step 2: Bind Socket to Local Address
struct sockaddr_nl local = {
    .nl_family = AF_NETLINK,
    .nl_pid = getpid()
};

bind(sock, (struct sockaddr *)&local, sizeof(local));

Why bind?

Kernel needs a PID to reply to

nl_pid = getpid() uniquely identifies user process

Kernel uses nl_pid to send replies.

Step 3: Build Netlink Request Message
3.1 Netlink Message Header (nlmsghdr)
struct nlmsghdr *nlh;

Field		Purpose
nlmsg_len	Total length of message
nlmsg_type	Command (RTM_GETROUTE, RTM_GETLINK…)
nlmsg_flags	Request, dump, ack
nlmsg_seq	Sequence number
nlmsg_pid	Sender PID

Example:

nlh->nlmsg_type  = RTM_GETROUTE;
nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;

3.2 Message Payload (Subsystem Specific)

Depends on message type:

Command	Payload
RTM_GETROUTE	struct rtmsg
RTM_GETLINK	struct ifinfomsg
RTM_GETADDR	struct ifaddrmsg
RTM_GETNEIGH	struct ndmsg
RTM_GETRULE	struct fib_rule_hdr

Example (route):

struct rtmsg *rtm = NLMSG_DATA(nlh);
rtm->rtm_family = AF_INET;

Step 4: Send Message to Kernel
struct sockaddr_nl kernel = {
    .nl_family = AF_NETLINK
};

sendto(sock, nlh, nlh->nlmsg_len, 0,
       (struct sockaddr *)&kernel, sizeof(kernel));

Key point

Destination PID = 0 → kernel

Kernel parses request and prepares response

Step 5: Receive Kernel Replies

Kernel may send:

Multiple messages

Terminated by NLMSG_DONE

recv(sock, buffer, sizeof(buffer), 0);

Loop through messages
for (nlh = (struct nlmsghdr *)buffer;
     NLMSG_OK(nlh, len);
     nlh = NLMSG_NEXT(nlh, len)) {

Step 6: Parse Reply Attributes (Important)

Netlink replies are attribute-based.

| nlmsghdr |
| payload  |
| rtattr   |
| rtattr   |
| ...      |

Generic attribute format
struct rtattr {
    unsigned short rta_len;
    unsigned short rta_type;
    /* data follows */
};

Example: Route Attributes
Attribute	Meaning
RTA_DST	Destination prefix
RTA_GATEWAY	Next-hop IP
RTA_OIF	Output interface index

Code:

struct rtattr *attr = RTM_RTA(rtm);
int alen = RTM_PAYLOAD(nlh);

for (; RTA_OK(attr, alen); attr = RTA_NEXT(attr, alen)) {
    switch (attr->rta_type) {
    case RTA_DST:
        inet_ntop(AF_INET, RTA_DATA(attr), dst, sizeof(dst));
        break;
    case RTA_GATEWAY:
        inet_ntop(AF_INET, RTA_DATA(attr), gw, sizeof(gw));
        break;
    }
}

7. Example Walk-Through: ip route show
User command
ip route show

Netlink equivalent

Socket: NETLINK_ROUTE

Message: RTM_GETROUTE

Flags: NLM_F_DUMP

Kernel reply

Multiple RTM_NEWROUTE messages:

dst=default gw=192.168.1.1 oif=2

8. Example Walk-Through: ARP Table
User command
ip neigh show

Netlink

Message: RTM_GETNEIGH

Payload: struct ndmsg

Attributes:
Attribute	Meaning
NDA_DST	IP 	address
NDA_LLADDR	MAC address

9. Common Netlink Message Mapping
CLI Command	Netlink Message
ip link show	RTM_GETLINK
ip addr show	RTM_GETADDR
ip route show	RTM_GETROUTE
ip neigh show	RTM_GETNEIGH
ip rule show	RTM_GETRULE
10. Key Interview Takeaways


Netlink is attribute-based

Kernel replies may be multi-part

NLMSG_DONE ends a dump

Attributes must be parsed using RTA_OK

Each ip command maps to RTM_GET* message

11. One-line Interview Answer (Gold)

“Every Netlink program follows the same model: create socket, bind PID, send RTM_GET request, receive multipart replies, and parse rtattr attributes.”

