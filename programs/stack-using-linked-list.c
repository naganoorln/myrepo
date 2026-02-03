#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	int data;
	struct Node* next;
}NODE;

typedef struct stack
{
	NODE* top;
}STACK;


void initializeStack(STACK *st)
{
	st->top = NULL;
}
void push(STACK* st, int value)
{
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = value;	
    newnode->next = st->top;
	st->top = newnode;
        	
}
int pop(STACK* st)
{
	if(st->top == NULL)
	{
		printf("Stack is empty.\n");
		return 0;
	}
	int data = st->top->data;
	NODE* temp = st->top;
	st->top = st->top->next;
	free(temp);
	return data;    
}

void display(STACK* st)
{
        NODE* temp = st->top;
        while(temp != NULL)
        {
                printf("%d ", temp->data);
                temp = temp->next;
        }
        printf("\n");
}


int main()
{
	STACK st;
    initializeStack(&st);
	push(&st, 10);
    push(&st, 20);
    push(&st, 30);
    push(&st, 40);
    push(&st, 50);
    display(&st);
    int data = pop(&st);
    printf("%d\n", data);
    return 0;
}

