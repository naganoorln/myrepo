#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
}QUEUENODE;

typedef struct Queue
{
	QUEUENODE* front;
	QUEUENODE* rear;
}QUEUE;

QUEUE* createQueue()	
{
	QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
	q->front = q->rear = NULL;
	return q;
}

int isQueueEmpty(QUEUE* q)
{
	return (q->front == NULL);
}

void enqueue(QUEUE* q, int value)
{
	QUEUENODE* temp = (QUEUENODE*)malloc(sizeof(QUEUENODE));
	temp->data = value;
	temp->next = NULL;
	if(isQueueEmpty(q))
	{
		q->front = q->rear = temp;
		return ;
	}
	q->rear->next = temp;
	q->rear = temp;
}

int dequeue(QUEUE* q)
{
	if(isQueueEmpty(q))
	{
		printf("Queue is empty!.\n");
		return -1; 
	}
	QUEUENODE* temp = q->front;
	int data = temp->data;
	q->front = q->front->next;
	if(q->front == NULL)
		q->rear = NULL;
	free(temp);
	return data;
}

int peak(QUEUE* q)
{
	if(isQueueEmpty(q))
	{
		printf("Queue is empty!.\n");
		return -1;
	}
	return q->front->data;
}

void printQueue(QUEUE* q)
{
	if(isQueueEmpty(q))
	{
		printf("Queue is empty!.\n");
		return;
	}
	QUEUENODE* temp = q->front;
	while(temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
	QUEUE* q = createQueue();
	enqueue(q, 10);
	enqueue(q, 20);
	enqueue(q, 30);
	enqueue(q, 40);
	enqueue(q, 50);
	printf("Queue:");
	printQueue(q);
	printf("Dqueue:%d\n", dequeue(q));
	printf("Queue:");
        printQueue(q);
	printf("Peak:%d\n", peak(q));
	return 0;
}


	



