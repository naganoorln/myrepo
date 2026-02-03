#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define RING_SIZE 1024
#define PACKET_SIZE 1500
#define MCAST_GROUP "239.1.1.1"
#define MCAST_PORT  5000
int main()
{
    int sock;
    struct sockaddr_in addr;
    char msg[PACKET_SIZE] = "Hello Multicast";

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(MCAST_GROUP);
    addr.sin_port = htons(MCAST_PORT);

    while (1) {
        sendto(sock, msg, strlen(msg) + 1, 0,
               (struct sockaddr *)&addr, sizeof(addr));
        sleep(1);
    }
}

