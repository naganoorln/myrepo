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

STACK* createStack()
{
	STACK* s = (STACK*)malloc(sizeof(STACK));
	s->top = NULL;
	return s;
}

void push(STACK* s, int value)
{
	STACKNODE* temp = (STACKNODE*)malloc(sizeof(STACKNODE));
	temp->data = value;
	temp->next = s->top;
	s->top = temp;
}

int isStackEmpty(STACK* s)
{
	return (s->top == NULL);
}
int pop(STACK* s)
{
	if(isStackEmpty(s))
	{
		printf("Stack is empty!.\n");
		return -1;
	}
	STACKNODE* temp = s->top;
	int data = temp->data;
	s->top = s->top->next;
	free(temp);
	return data;
}

void printStack(STACK* s)
{
	STACKNODE* temp = s->top;
	while(temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
	STACK* s = createStack();
	push(s, 10);
	push(s, 20);
	push(s, 30);
	push(s, 40);
	push(s, 50);
	printf("Stack:");
	printStack(s);
	printf("Pop:%d", pop(s));
	printf("\nStack:");
	printStack(s);
	printf("Pop:%d", pop(s));
	printf("\nStack:");
	printStack(s);
	return 0;
}