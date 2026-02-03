#include <stdio.h>
#include <stdlib.h>
/* Delete a node from a list end */
struct Node
{
	int data;
	struct Node* next;
};
void deleteNodeFromListEnd(struct Node** head, int pos)
{
	struct Node* first = *head;
    struct Node* second = *head;
	int count = 0;	
	
	while(count < pos)
	{
	    if(first == NULL)
		{
			printf("Number of nodes is less than %d\n",pos);
			return;
		}
		first = first->next;
		count++;
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
struct Node* createNode(int value)
{
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = value;
	newnode->next = NULL;
	return newnode;
}
void printList(struct Node* head)
{
	while(head != NULL)
	{
		printf("%d ",head->data);
		head = head->next;
	}
	printf("\n");
}
int main()
{
	struct Node *head = createNode(1);
	head->next = createNode(2);
	head->next->next = createNode(3);
	head->next->next->next = createNode(4);
	head->next->next->next->next = createNode(5);
	printf("List before deleting.\n");
	printList(head);
	deleteNodeFromListEnd(&head, 4);
	printf("List after deleting.\n");
	printList(head);
	return 0;
}