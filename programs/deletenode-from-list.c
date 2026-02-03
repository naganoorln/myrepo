/* Delete node from linked list */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Define List node*/
struct Node 
{
    int data;
    struct Node* next;
};
/* Create node*/
struct Node* createNode(int value)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}
/* Insert node */
void insertNode(struct Node** head, int value)
{
    struct Node* newnode = createNode(value);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    struct Node* current = *head;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = newnode;
}
void deleteNode(struct Node** head, int key, bool* present)
{
    struct Node* temp = *head;
    struct Node* prev = NULL;
    if(*head != NULL && (*head)->data == key)
    {
        (*head) = (*head)->next;
        free(temp);
        *present = true;
        return;
    }
    while(temp != NULL && temp->data != key)
    {
            prev = temp;
            temp = temp->next;
    }
    if(temp == NULL)
    {
        return;
    }
    prev->next = temp->next;
    *present = true;
    free(temp);
}
/* Print linked list */
void printList(struct Node* head)
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
    bool keyPresent = false;
    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);
    insertNode(&head, 40);
    insertNode(&head, 50);
    printf("Original List: ");
    printList(head);
    deleteNode(&head, 100, &keyPresent);
    if(!keyPresent)
    {
        printf("Key is not present in the list.\n");
        return 0;
    }
    printf("List after deletion: ");
    printList(head);
    return 0;
}