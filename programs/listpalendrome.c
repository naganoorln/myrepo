#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
void insertNode(struct Node** head, int value)
{
    struct Node* newnode = createNode(value);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    struct Node* temp = *head;
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = newnode;
}
bool checkListIsPalendrome(struct Node* head)
{
    if(head == NULL)
    {
        return true;
    }
    struct Node* slow = head;
    struct Node* fast = head;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct Node* prev = NULL;
    struct Node* next = NULL;
    while(slow)
    {
        next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }
    struct Node* left = head;
    struct Node* right = prev;
    while(right)
    {
        if(left->data != right->data)
        {
            return false;
            
        }
        left = left->next;
        right = right->next;
    }
    return true;
}
void printList(struct Node* head)
{
    while(head)
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
    insertNode(&head, 12);
    insertNode(&head, 13);
    insertNode(&head, 12);
    insertNode(&head, 10);
    printf("List: ");
    printList(head);
    bool isp = checkListIsPalendrome(head);
    printf("List is %s", isp ? "palendrome." : "not palendrome.");
    return 0;
}


