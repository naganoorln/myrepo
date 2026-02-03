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
	if(!(*head))
	{
		*head = newnode(value);
		return;
	}
	struct Node* temp = *head;
	while(temp->next)
		temp = temp->next;
	temp->next = newnode(value);
}
void deleteNthnode(struct Node** head, int n)
{
	if(*head == NULL || n <= 0)
		return;
	struct Node* first = *head;
	struct Node* second = *head;
	int count = 0;

	while(count < n)
	{
		if(!first)
		{
			printf("Less than %d elements in the List.\n", n);
			return;
		}
		first = first->next;
		count++;
	}
	struct Node* prev = NULL;
	while(first)
	{
		prev = second;
		first = first->next;
		second = second->next;
	}
	if(prev)
	{
		prev->next = second->next;
	} else {
		*head = second->next;
	}
	free(second);
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
	int n = 6;
        deleteNthnode(&head, n);
	printf("List after delete:");
	display(head);
	return 0;
}
