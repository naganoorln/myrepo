#include <stdio.h>
#include <stdlib.h>

/* Node structure */
typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

/* Queue structure with front and rear pointers */
typedef struct Queue 
{
    Node* front;
    Node* rear;
} Queue;

/* Function to create a queue */
Queue* createQueue() 
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

/* Check if queue is empty */
int isEmpty(Queue* q) 
{
    return (q->front == NULL);
}

/* Enqueue: Insert element at rear */
void enqueue(Queue* q, int value) 
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    temp->next = NULL;
    if (q->rear == NULL) 
    {  /* first element */
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

/* Dequeue: Remove element from front */
int dequeue(Queue* q) 
{
    if (isEmpty(q)) 
    {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    /* if queue becomes empty */
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return value;
}

/* Peek: show front element */
int peek(Queue* q) 
{
    if (isEmpty(q)) 
    {
        printf("Queue is empty.\n");
        return -1;
    }
    return q->front->data;
}

/* Display queue */
void display(Queue* q) 
{
    if (isEmpty(q)) 
    {
        printf("Queue is empty.\n");
        return;
    }

    Node* temp = q->front;
    printf("Queue: ");
    while (temp != NULL) 
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/* Test the queue */
int main() 
{
    Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);
    printf("Dequeued: %d\n", dequeue(q));
    printf("Front element: %d\n", peek(q));
    display(q);
    return 0;
}

