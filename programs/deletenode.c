#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node* next;
};

struct Node* createnode(int value)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

void insertnode(struct Node** head, int value)
{
    if(*head == NULL)
    {
        *head = createnode(value);
        return;
    }
    struct Node* current = *head;
    while(current->next != NULL)
        current = current->next;
    current->next = createnode(value);
}
void printlist(struct Node* head)
{
    struct Node* temp = head;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void deleteNthNodeFromListEnd(struct Node** head, int n)
{
    struct Node* first = *head;
    struct Node* second = *head;
    if(*head == NULL)
    {
        printf("List is empty!.\n");
        return;
    }
        
    if(n <= 0)
    {
        printf("n should be greater than 0\n");
        return;
    }
    for(int i = 0; i < n; i++)
    {
        if(first == NULL)
        {
            printf("Number of nodes in the given list is less than %d nodes\n", n);
            return;
        }
        first = first->next;
    }
    if(first == NULL) 
    {
        *head = second->next;
        free(second);
        return;
    }
    while(first->next != NULL)
    {
        second = second->next;
        first = first->next;
    }
    struct Node* temp = second->next;
    second->next = second->next->next;
    free(temp);
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
    printlist(head);
    deleteNthNodeFromListEnd(&head, 0);
    printf("List:");
    printlist(head);
    return 0;
}
