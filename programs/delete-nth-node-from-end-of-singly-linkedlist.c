#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node* next;
}NODE;
NODE* createNode(int value)
{
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}
void insertNode(NODE** head, int value)
{
    NODE* newnode = createNode(value);
    if(!(*head))
    {
        *head = newnode;
        return;
    }
    NODE* current = *head;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = newnode;
}
void deleteNthNodeFromEnd(NODE** head, int pos)
{   
    NODE* first = *head;
    NODE* second = *head;
    int count = 0;
    while(count < pos)
    {
        if(!first)
        {
            printf("Number of nodes is less than %d\n", pos);
            return;
        }
        first = first->next;
        count++;
    }
    
    NODE* prev = NULL;
    while(first != NULL)
    {
        prev = second;
        first = first->next;
        second = second->next;
    }
    if(prev != NULL)
    {
        prev-> next = second->next;
    } else {
        *head = second->next;
    }
    free(second);
}
void displayList(NODE* head)
{
    NODE* current = head;
    while(current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main()
{
    NODE* head = NULL;
    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);
    insertNode(&head, 40);
    insertNode(&head, 50);
    printf("Original List:");
    displayList(head);
    deleteNthNodeFromEnd(&head, 5);
    printf("List after deletion:");
    displayList(head);
    return 0;
}