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
    struct Node* newnode = createnode(value);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    struct Node* temp = *head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = newnode;
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
:q!
    :q!
    :q!
}

struct Node* listreverserec(struct Node* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    struct Node* newhead = listreverserec(head->next);
    head->next->next = head;
    head->next = NULL;
    return newhead;
    /* Step-by-Step Recursion Trace (Very Important)
    Initial List:
    10 → 20 → 30 → 40 → NULL
    Recursive Calls (Going Down)
    reverse(10)
    └── reverse(20)
        └── reverse(30)
            └── reverse(40)
    Base Case Hit
    reverse(40) → returns 40
    Unwinding (Coming Back)
    At node 30
    30->next->next = 30  -> 40->next = 30 
    30->next = NULL
    List becomes:
    40 → 30 → NULL
    At node 20
    20->next->next = 20  -> 30->next = 20  
    20->next = NULL
    List becomes:
    40 → 30 → 20 → NULL
    At node 10
    10->next->next = 10  -> 20->next = 10 
    10->next = NULL
    Final list:
    40 → 30 → 20 → 10 → NULL
    Dry Run (Interview Style)
    Call Stack head Action
    reverse(40) 40 return
    reverse(30) 30 link 40→30
    reverse(20) 20 link 30→20
    reverse(10) 10 link 20→10 */
}

int main()
{
    struct Node* head = NULL;
    insertnode(&head, 10);
    insertnode(&head, 20);
    insertnode(&head, 30);
    insertnode(&head, 40);
    printf("Original List:");
    printlist(head);
    struct Node* newhead = listreverserec(head);
    printf("Reversed List:");
    printlist(newhead);
    return 0;
}
