#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*typedef void (*Callback)();

void fun()
{
    printf("fun called\n");
}

int callbackFun(Callback cf)
{
    cf();
}

int main()
{
    callbackFun(fun);
    return 0;
}*/

/*void ieverseString(char* str)
{
    int len = strlen(str) - 1;
    while(len >= 0)
    {
        printf("%c", str[len]);
        len--;
    }
    printf("\n");
}

int main()
{
    char str[] = "Hello world";
    reverseString(str);
    return 0;
}*/

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
    if(*head == NULL)
    {
        *head = createNode(value);
        return;
    }
    struct Node* temp = *head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = createNode(value);
}

void displayList(struct Node* head)
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
    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);
    insertNode(&head, 40);
    insertNode(&head, 50);
    displayList(head);
    return 0;
}



