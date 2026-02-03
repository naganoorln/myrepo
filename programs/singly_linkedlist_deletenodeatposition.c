/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node* next;
};

void createNode(struct Node** head, int value)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if(!(*head))
    {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    *head = newNode;
}

void printList(struct Node* head)
{
    while(head)
    {
        printf("%d ",head->data);
        head = head->next;
    }
    printf("\n");
}

void deleteNodeAtPosition(struct Node** head, int position)
{
    struct Node *temp = *head;
    if(*head == NULL)
    {
        return;
    }
    if(position == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }
    struct Node* prev = NULL;
    int count = 1;
    while(temp->next)
    {
        prev = temp;
        temp = temp->next;
        count++;
        if(count == position)
        {
            prev->next = temp->next;
            free(temp);
            return;
        }
    }
}
int main()
{
    struct Node *head = NULL;
    int position = 4;
    createNode(&head, 1);
    createNode(&head, 2);
    createNode(&head, 3);
    createNode(&head, 4);
    createNode(&head, 5);
    printf("Original List: ");
    printList(head);
    deleteNodeAtPosition(&head, position);
    deleteNodeAtPosition(&head, 2);
    printf("Modified List: ");
    printList(head);
    return 0;
}
