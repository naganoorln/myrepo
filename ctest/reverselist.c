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
	if(*head == NULL)
        {
		*head = newnode(value);
		return;
	}
	struct Node* temp = *head;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = newnode(value);
}

void reverselist(struct Node** head)
{
	struct Node* current = *head;
	struct Node* next = NULL;
	struct Node* prev = NULL;
        while(current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

void display(struct Node* head)
{
	while(head)
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
	reverselist(&head);
	printf("List after reverse:");
	display(head);
	return 0;
}
