#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

struct Node* newnode(int value)
{
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = value;
	newnode->next = NULL;
	return newnode;
}

void insert(struct Node** head, int value)
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

void delete(struct Node** head, int key)
{
    if((*head) == NULL)
        return;
    struct Node* temp = *head;
    if(temp->data == key)
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
        printf("No %d key found in list\n", key);
        return;
    }
    prev->next = temp->next;
    free(temp);
}
void deleteByPos(struct Node** head, int pos)
{
    struct Node* temp = *head;
    if(temp == NULL || pos < 0)
    {
        printf("Either list is empty or invalid position\n");
        return;
    }
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
        printf("Less than %d elements in the list\n", pos);
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void printList(struct Node* head)
{
    struct Node* temp = head;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    struct Node* head = NULL;
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);
    insert(&head, 40);
    insert(&head, 50);
    printf("List:");
    printList(head);
    int key = 30;
    delete(&head, key);
    printf("List after delete:");
    printList(head);
    int pos = 3;
    deleteByPos(&head, pos);
    printf("List after deleteByPos:");
    printList(head);
    return 0;
}

