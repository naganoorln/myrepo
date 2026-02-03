#include <stdio.h> 
#include <stdlib.h>
struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};
void reverseLinkedList(struct Node** head)
{
    struct Node* current = *head;
    struct Node* temp = NULL;
    while(current != NULL)
    {
        temp = current->prev;
        current->prev= current->next;
        current->next = temp;
        current = current->prev;
    }
    if(temp != NULL)
        *head = temp->prev;
}
void push(struct Node** head, int data)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->prev= NULL;
    newnode->next = *head;
    if(*head != NULL)
        (*head)->prev = newnode;
    (*head) = newnode;
}
void print(struct Node* head)
{
    while(head != NULL)
    {
        printf("%d ",head->data);
        head= head->next;
    }
}
int main()
{
    struct Node *head = NULL;
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    push(&head, 6);
    printf("\n Original Linked List ");
    print(head);
    reverseLinkedList(&head);
    printf("\n Reversed Linked List ");
    print(head);
}

