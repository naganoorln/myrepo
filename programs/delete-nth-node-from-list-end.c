/* Delete a node from list end */
#include <stdio.h>
#include <stdlib.h>
struct Node 
{
    int data;
    struct Node* next;
};
void deleteNodeFromListend(struct Node** head, int pos)
{
    struct Node* first = *head;
    struct Node* second = *head;
    int count = 0;
    while(count < pos)
    {
        if(first == NULL)
        {
            printf("Number of nodes is less than %d nodes\n",pos);
        }
        first = first->next;
        count++;
    }
    struct Node* prev = NULL;
    while(first != NULL)
    {
        prev = second;
        second = second->next;
        first = first->next;
    }
    if(prev != NULL)
    {
        prev->next = second->next;
    } else {
        *head = second->next;
    }
    free(second);
}
struct Node* createNode(int value)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}
struct Node* insertNode(struct Node* head, int value)
{
    if(head == NULL)
    {
        return createNode(value);
    }
    while(head->next != NULL)
    {
        head = head->next;
    }
    head->next = createNode(value);
}
void printNode(struct Node* head)
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
    head = insertNode(head, 10);
    insertNode(head, 20);
    insertNode(head, 30);
    insertNode(head, 40);
    insertNode(head, 50);
    printNode(head);
    deleteNodeFromListend(&head, 6);
    printNode(head);
    return 0;
}



