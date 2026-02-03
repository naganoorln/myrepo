#include <stdio.h>
#include <stdlib.h>
typedef struct stacknode
{
	int data;
	struct stacknode* next;
} STACKNODE;

typedef struct Stack
{
	STACKNODE* top;
} STACK;

void initializestack(STACK* st)
{
	st->top = NULL;
}

void push(STACK* st, int value)
{
	STACKNODE* newstacknode = (STACKNODE*)malloc(sizeof(STACKNODE));
	newstacknode->data = value;
	newstacknode->next = st->top;
	st->top = newstacknode;
}

int pop(STACK* st)
{
	if(st->top == NULL)
	{
		printf("Stack is empty.\n");
		return -1;
	}
	int data = st->top->data;
	STACKNODE* temp = st->top;
	st->top = st->top->next;
	free(temp);
	return data;
}

void displaystack(STACK* st)
{
	STACKNODE* temp = st->top;
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
	initializestack(&st);
	push(&st, 10);
	push(&st, 20);
	push(&st, 30);
	push(&st, 40);
	push(&st, 50);
	printf("Stack: ");
	displaystack(&st);
	printf("Pop: %d", pop(&st));
	printf("\nStack: ");
	displaystack(&st);
	return 0;
}