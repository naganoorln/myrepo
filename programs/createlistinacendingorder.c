/* Insert a node in ascending order in singly linked list */
#include <stdio.h>
#include <stdlib.h>
struct Node 
{
    int data;
    struct Node* next;
};
struct Node* createNode(int value)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}
void insertNodeInAcendingOrder(struct Node** head, int value)
{
    struct Node* newnode = createNode(value);
    if(*head == NULL || (*head)->data >= value)
    {
        newnode->next = *head;
        *head = newnode;
        return;
    }
    struct Node* current = *head;
    while(current->next != NULL && current->next->data < value)
    {
        current = current->next;
    }
    newnode->next = current->next;
    current->next = newnode;
}
void printLinkedList(struct Node* head)
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
    insertNodeInAcendingOrder(&head, 10);
    insertNodeInAcendingOrder(&head, 7);
    insertNodeInAcendingOrder(&head, 29);
    insertNodeInAcendingOrder(&head, 5);
    insertNodeInAcendingOrder(&head, 22);
    printLinkedList(head);
    return 0;
}