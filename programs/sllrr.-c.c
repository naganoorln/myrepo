#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};

struct Node* createnode(int data)
{
	struct Node* newnode = malloc(sizeof(struct Node));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

void insertnode(struct Node** head, int data)
{
	struct Node* newnode = createnode(data);
	if (*head == NULL) {
		*head = newnode;
		return;
	}
	struct Node* temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = newnode;
}

void printlist(struct Node* head)
{
	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

/* p Recursive Reverse Function */
struct Node* reverseRecursive(struct Node* head)
{
	/* Base case */
	if (head == NULL || head->next == NULL)
		return head;

	/* Reverse rest of the list */
	struct Node* newHead = reverseRecursive(head->next);

	/* Fix current node */
	head->next->next = head;
	head->next = NULL;

	return newHead;
}

int main()
{
	struct Node* head = NULL;

	insertnode(&head, 10);
	insertnode(&head, 20);
	insertnode(&head, 30);
	insertnode(&head, 40);

	printf("Original list: ");
	printlist(head);

	head = reverseRecursive(head);

	printf("Reversed list: ");
	printlist(head);

	return 0;
}