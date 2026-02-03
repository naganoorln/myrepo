#include <stdio.h>
#include <stdlib.h>
struct Node 
{
    int data;
    struct Node* next;
};

struct Node* craeteNode(int value)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}
void insertNode(struct Node** head, int value)
{
    struct Node* newnode = craeteNode(value);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    struct Node* current = *head;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = newnode;
}
void deleteNode(struct Node** head, int value)
{
    struct Node* temp = *head;
    if(*head == NULL )
    {
        return;
    }
    if((*head)->data == value)
    {
        *head = (*head)->next;
        free(temp);
        return;
    }
    struct Node* prev = NULL;
    while(temp != NULL && temp->data != value)
    {
        prev = temp;
        temp = temp->next;
        
    }
    prev->next = temp->next;
    free(temp);
}
void printList(struct Node* head)
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
   insertNode(&head, 10);
   insertNode(&head, 20);
   insertNode(&head, 30);
   insertNode(&head, 40);
   insertNode(&head, 50);
   printf("Original list: ");
   printList(head);
   deleteNode(&head, 30);
   printf("List after deleation: ");
   printList(head);
   return 0;
}
