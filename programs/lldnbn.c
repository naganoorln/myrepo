#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* createnode(int value)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

void insertnode(struct Node** head, int value)
{
    if((*head) == NULL)
    {
        *head = createnode(value);
        return;
    }
    struct Node*temp = *head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = createnode(value);
}
struct Node* reverseListRecrse(struct Node* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    struct Node* newhead = reverseListRecrse(head->next);
    head->next->next = head;
    head->next = NULL;
    return newhead;
}
void deletenode(struct Node* node)
{
    if(node == NULL)
        return;
    struct Node* temp = node->next;
    node->data = temp->data;
    node->next = temp->next;
    free(temp);
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

int main()
{
    struct Node* head = NULL;
    insertnode(&head, 10);
    insertnode(&head, 20);
    insertnode(&head, 30);
    insertnode(&head, 40);
    insertnode(&head, 50);
    insertnode(&head, 60);
    printf("List:");
    printlist(head);
    struct Node* temp = head->next;
    printf("List After Deleting Node With Data %d",temp->data);
    deletenode(temp);
    printf("\nList:");
    printlist(head);
    printf("Reverse List:");
    head = reverseListRecrse(head);
    printlist(head);
    return 0;
}