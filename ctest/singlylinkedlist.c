#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

struct Node* newnode(int value)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = value;
	node->next = NULL;
	return node;
}

void insertnode(struct Node** head, int value)
{
	if((*head) == NULL)
	{
		(*head) = newnode(value);
		return;
	}
	struct Node* temp = *head;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = newnode(value);
}

void deletenode(struct Node** head, int key)
{	
	if(*head == NULL)
		return;
	struct Node* temp = *head;
	if((*head)->data == key)
	{
		*head = temp->next;
		free(temp);
		return;
	}
	struct Node* prev = NULL;
	while(temp != NULL && temp->data != key)
	{
		prev = temp;
		temp = temp->next;
	}
	if(temp == NULL)
	{
		printf("%d is not present in the List.\n", key);
		return;
	}
	prev->next = temp->next;
	free(temp);
}	

void deletenodebypos(struct Node** head, int pos)
{
	if(*head == NULL || pos < 0)
	{
		printf("Either list is empty or invalid position.\n");
		return;
	}
	struct Node* temp = *head;
	if(pos == 0)
	{
		*head = temp->next;
		free(temp);
		return;
	}
	struct Node* prev = NULL;
	for(int i = 0; temp != NULL && i < pos; i++)
	{
		prev = temp;
		temp = temp->next;
	}
	if(temp == NULL)
	{
		printf("Number of elements are less than %d elements.\n", pos);
		return;
	}
	prev->next = temp->next;
	free(temp);
}




void display(struct Node* head)
{
	while(head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

int main()
{
	struct Node* head = NULL;
	insertnode(&head, 10);
	insertnode(&head, 20);
	insertnode(&head, 30);
	insertnode(&head, 40);
	insertnode(&head, 50);
	printf("List:");
	display(head);
	//deletenode(&head, 30);
	//printf("List after delete:");
	deletenodebypos(&head, 5);
	display(head);
	return 0;
}


