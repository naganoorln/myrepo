#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int pid;
	char pname[20];
	int burst_time;
	int priority;
} Process;
typedef struct Node
{
	Process data;
	struct Node* next;
} Node;
Node* createNode(Process data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}
int isQueueEmpty(Node** head)
{
	return *head == NULL;
}
void enQueue(Node** head, Process data)
{
	Node* start = *head;
	Node* newnode = createNode(data);
	if(isQueueEmpty(head) || (*head)->data.priority > data.priority)
	{
		newnode->next = *head;
		(*head) = newnode;
	} else {
		while(start->next!= NULL && start->next->data.priority <= data.priority)
		{
			start = start->next;
		}
		newnode->next = start->next;
		start->next = newnode;
	}
}
void deQueue(Node** head)
{
	if(isQueueEmpty(head))
	{
		printf("Queue is empty.\n");
		return;
	}
	Node* temp = *head;
	*head = (*head)->next;
	free(temp);
}
Process peek(Node** head)
{
	if(isQueueEmpty(head))
	{
		printf("Queue is empty.\n");
		Process empty_process = {0, "", 0, 0};
		return empty_process;
	}
	return (*head)->data;
}
void displayQueue(Node* head)
{
	if(isQueueEmpty(&head))
	{
		printf("Queue is empty.\n");
		return;
	}
	Node* temp = head;
	while(temp != NULL)
	{
		printf("pid: %d\nprocess Name: %s\nburst_time: %d\npriority: %d\n\n",
		       temp->data.pid,temp->data.pname,temp->data.burst_time,temp->data.priority);
		temp = temp->next;
	}
}
int main()
{
	Node* pq = NULL;
	Process p1 = {101, "ProcessA", 10, 2};
	Process p2 = {102, "ProcessB", 5, 1};
	Process p3 = {101, "ProcessC", 8, 3};
	enQueue(&pq, p1);
	enQueue(&pq, p1);
	enQueue(&pq, p1);
	//Display the Queue
	printf("Priority Queue:\n\n");
	displayQueue(pq);
	return 0;
}


