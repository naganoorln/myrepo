#include <stdio.h>
#define MAX 20
typedef struct Queue 
{
    int items[MAX];
    int front;
    int rear;
}QUEUE;
void initializeQueue(QUEUE* q)
{
    q->front = q->rear = -1;
}
int isQueueFull(QUEUE* q)
{
    return q->rear == MAX -1 ;
}
int isQueueEmpty(QUEUE* q)
{
    return q->front == -1;
}
void enqueue(QUEUE* q, int value)
{
    if(isQueueFull(q))
    {
        printf("Queue is full!.\n");
        return;
    }
    if(isQueueEmpty(q))
    {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}
int dequeue(QUEUE* q)
{
    if(isQueueEmpty(q))
    {
        printf("Queue is empty!.\n");
        return -1;
    }
    int value = q->items[q->front++];
    if(q->front > q->rear)
    {
        q->front = q->rear = -1;
    }
    return value;
}
int peek(QUEUE* q)
{
    if(isQueueEmpty(q))
    {
        printf("Queue is empty!.\n");
        return -1;
    }
    return q->items[q->front];
}
void dispalyQueue(QUEUE* q)
{
    if(isQueueEmpty(q))
    {
        printf("Queue is empty!.\n");
        return;
    }
    for(int i = q->front; i <= q->rear; i++)
    {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}
int main()
{
    QUEUE q;
    initializeQueue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    printf("Original Queue:");
    dispalyQueue(&q);
    printf("Peek of the Queue:%d\n",peek(&q));
    printf("Element dequeued:%d\n", dequeue(&q));
    printf("Queue after dequeue:");
    dispalyQueue(&q);
    printf("Peek of the Queue after dequeue:%d\n",peek(&q));
    return 0;
}
