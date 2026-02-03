#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	int data;
	struct Node* next;
} NODE;

NODE* createNode(int value)
{
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode->data = value;
	newnode->next = NULL;
	return newnode;
}
void insertNode(NODE** head, int value)
{
	if(!(*head))
	{
		(*head) = createNode(value);
		return;
	}
	NODE* temp = (*head);
	while(temp->next)
	{
		temp = temp->next;
	}
	temp->next = createNode(value);
}
void displayList(NODE* head)
{
	NODE* temp = head;
	while(temp)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
int main()
{
	NODE* head = NULL;
	insertNode(&head, 10);
	insertNode(&head, 20);
	insertNode(&head, 30);
	insertNode(&head, 40);
	insertNode(&head, 50);
	displayList(head);
	return 0;
}
