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
}
void insertNode(struct Node** head, int value)
{
    if(*head == NULL)
    {
        *head = createNode(value);
        return;
    }
    struct Node *temp = *head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = createNode(value);
}
void displayList(struct Node* head)
{
    while(head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
void detectLoopAndRemoveInList(struct Node* head)
{
    struct Node* slow = head;
    struct Node* fast = head;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
        {
            break;
        }
    }
    if(slow == fast)
    {
        slow = head;
        if(slow == fast)
        {
            while(fast->next != slow)
            {
                fast = fast->next;
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
int main()
{
    struct Node* head = NULL;
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    //struct Node *temp1 = head->next->next;
    insertNode(&head, 4);
    struct Node *temp1 = head->next->next->next;
    insertNode(&head, 5);
    insertNode(&head, 6);
    insertNode(&head, 7);
    insertNode(&head, 8);
    struct Node* temp2 = head->next->next->next->next->next->next->next;
    printf("Orginal List:");
    displayList(head);
    temp2->next = temp1;
    //printf("List with loop:");
    //displayList(head);
    detectLoopAndRemoveInList(head);
    printf("List after removing loop:");
    displayList(head);
    return 0;
}