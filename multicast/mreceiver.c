
#include <pthread.h>
#include <string.h>
#include <stdio.h>

#define RING_SIZE 1024
#define PACKET_SIZE 1500

typedef struct 
{
    char data[RING_SIZE][PACKET_SIZE];
    int head;
    int tail;
    int count;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} ring_buffer_t;

void ring_init(ring_buffer_t *rb)
{
    rb->head = rb->tail = rb->count = 0;
    pthread_mutex_init(&rb->lock, NULL);
    pthread_cond_init(&rb->not_empty, NULL);
    pthread_cond_init(&rb->not_full, NULL);
}

void ring_push(ring_buffer_t *rb, char *pkt)
{
    pthread_mutex_lock(&rb->lock);

    while (rb->count == RING_SIZE)
        pthread_cond_wait(&rb->not_full, &rb->lock);

    memcpy(rb->data[rb->head], pkt, PACKET_SIZE);
    rb->head = (rb->head + 1) % RING_SIZE;
    rb->count++;

    pthread_cond_signal(&rb->not_empty);
    pthread_mutex_unlock(&rb->lock);
}

void ring_pop(ring_buffer_t *rb, char *pkt)
{
    pthread_mutex_lock(&rb->lock);

    while (rb->count == 0)
        pthread_cond_wait(&rb->not_empty, &rb->lock);

    memcpy(pkt, rb->data[rb->tail], PACKET_SIZE);
    rb->tail = (rb->tail + 1) % RING_SIZE;
    rb->count--;

    pthread_cond_signal(&rb->not_full);
    pthread_mutex_unlock(&rb->lock);
}

#define MCAST_GROUP "239.1.1.1"
#define MCAST_PORT  5000
#include <arpa/inet.h>
#include <unistd.h>

ring_buffer_t ring;

void *producer_thread(void *arg)
{
    int sock;
    struct sockaddr_in addr;
    struct ip_mreq mreq;
    char buffer[PACKET_SIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(MCAST_PORT);

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    while (1) 
    {
        recv(sock, buffer, PACKET_SIZE, 0);
        ring_push(&ring, buffer);   // PRODUCER
    }
}
void *consumer_thread(void *arg)
{
    char buffer[PACKET_SIZE];

    while (1) 
    {
        ring_pop(&ring, buffer);    // CONSUMER
        printf("Consumed packet: %s\n", buffer);
    }
}
int main()
{
    pthread_t prod, cons;

    ring_init(&ring);

    pthread_create(&prod, NULL, producer_thread, NULL);
    pthread_create(&cons, NULL, consumer_thread, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
