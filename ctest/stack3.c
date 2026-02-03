#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	int data;
	struct Node* next;
}NODE;

typedef struct Stack
{
	NODE* top;
}STACK;

STACK* createstack()
{
	STACK* s = (STACK*)malloc(sizeof(STACK));
	s->top = NULL;
	return s;
}

int isStackEmpty(STACK* s)
{
	return (s->top == NULL);
}

void push(STACK* s, int value)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->data = value;
	node->next = s->top;
	s->top = node;
}

int pop(STACK* s)
{
	if(isStackEmpty(s))
	{
		printf("Stack is empty!.\n");
		return -1;
	}
	NODE* temp = s->top;
	int data = s->top->data;
	s->top = s->top->next;
	free(temp);
	return data;
}

int peak(STACK* s)
{
	if(isStackEmpty(s))
	{
		printf("Stack is empty!.\n");
		return -1;
	}
	return s->top->data;
}

void printStack(STACK* s)
{
	NODE* temp = s->top;
	while(temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");

}

int main()
{
	STACK* s = createstack();
	push(s, 10);
	push(s, 20);
	push(s, 30);
	push(s, 40);
	push(s, 50);
	printf("Stack:");
	printStack(s);
	printf("Pop:%d\n", pop(s));
	printf("Stack:");
	printStack(s);
	printf("Peak:%d\n", peak(s));
	printf("Pop:%d\n", pop(s));
        printf("Stack:");
        printStack(s);
        printf("Peak:%d\n", peak(s));
        return 0;
}



