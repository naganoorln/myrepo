#include <stdio.h>
#include <stdlib.h>
struct Node
{
	int data;
	struct Node* next;
};
struct Node* createNode(int data)
{
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}
void deleteNodeFromEnd(struct Node** head, int pos)
{
	struct Node* first = *head;
	struct Node* second = *head;
	for(int i = 0; i < pos; i++)
	{
		if(first == NULL)
		{
			printf("List has less than %d nodes\n",pos);
			return ;
		}
		first = first->next;
	}
	struct Node* prev = NULL;
	while(first != NULL)
	{
		prev = second;
		second = second->next;
		first = first->next;
	}
	if(prev != NULL)
	{
		prev->next = second->next;
	} else {
		*head = second->next;
	}
	free(second);
}
void printList(struct Node* head)
{
	while(head!= NULL)
	{
		printf("%d ",head->data);
		head = head->next;
	}
	printf("\n");
}

int main()
{
	struct Node* head = createNode(1);
	head->next = createNode(2);
	head->next->next = createNode(3);
	head->next->next->next = createNode(4);
	head->next->next->next->next = createNode(5);
	printList(head);
	deleteNodeFromEnd(&head, 3);
	printList(head);
	return 0;
}