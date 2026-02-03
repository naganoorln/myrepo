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
    if(!(*head))
    {
        (*head) = createNode(value);
        return;
    }
    NODE* temp = (*head);
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = createNode(value);
}
void detectLoopAndRemove(NODE* head)
{
    if(!(head) || !(head->next))
    {
        return;
    }
    NODE* slow = head;
    NODE* fast = head;
    slow = slow->next;
    fast = fast->next->next;
    while(fast && fast->next)
    {
        if(slow == fast)
        {
            break;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    if(slow == fast)
    {
        slow = head;
        if(slow == fast)
        {
            while(fast->next != slow)
            {
                fast= fast->next;
            } 
        } else {
            while(slow->next != fast->next)
            {
                slow = slow->next;
                fast = fast->next;
            }   
        }
        fast->next = NULL;
    }
}
void displayList(NODE* head)
{
    NODE* temp = head;
    while(temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
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
    NODE* temp = head->next->next->next;
    printf("Original List: ");
    displayList(head);
    NODE* temp1 = head->next->next->next->next;
    temp1->next = temp;
    detectLoopAndRemove(head);
    printf("List after removing loop: ");
    displayList(head);
    return;
}
