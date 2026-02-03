#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10
// Define process
typedef struct
{
	int process_id;
	int brust_time;
} PROCESS;
// define process queue[PCB-program control block]
typedef struct
{
	PROCESS processes[MAX_QUEUE_SIZE];
	int front;
	int rear;
	int size;
	int timeslice;
} PROCESS_QUEUE;
// initialize process queue
void initialize(PROCESS_QUEUE* q, int timeslice)
{
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->timeslice = timeslice;
}
int isQueueEmpty(PROCESS_QUEUE* q)
{
	return q->size == 0;
}
int isQueueFull(PROCESS_QUEUE* q)
{
	return q->size == MAX_QUEUE_SIZE;
}
void enQueue(PROCESS_QUEUE* q, PROCESS p)
{
	if(isQueueFull(q))
	{
		printf("Queue is full\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->processes[q->rear] = p;
	q->size++;
}
PROCESS deQueue(PROCESS_QUEUE* q)
{
	if(isQueueEmpty(q))
	{
		PROCESS no_process = {-1, -1};
		return no_process;
	}
	PROCESS p = q->processes[q->front];
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	q->size--;
	return p;
}
void roundRobinScheduler(PROCESS_QUEUE* q)
{
	while(!isQueueEmpty(q))
	{
		PROCESS p = deQueue(q);
		if(p.brust_time <= q->timeslice)
		{
			printf("Processing the task %d for remaining time %d. Task completed\n",
			       p.process_id, p.brust_time);
		} else {

			printf("Processing the task %d for a time slice %d for remaining time %d\n",
			       p.process_id, q->timeslice, (p.brust_time - q->timeslice));
			p.brust_time -= q->timeslice;
			// re-add the process with updated brust time at the end of the Queue
			enQueue(q, p);
		}
	}
}
int main()
{
	PROCESS_QUEUE q;
	int timeslice = 10;
	initialize(&q, timeslice);
	PROCESS p1 = {1, 35};
	PROCESS p2 = {2, 37};
	PROCESS p3 = {3, 27};
	enQueue(&q, p1);
	enQueue(&q, p2);
	enQueue(&q, p3);
	roundRobinScheduler(&q);
	return 0;
}