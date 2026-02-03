#include <stdio.h>
#include <stdlib.h>
typedef struct Stacknode
{
	int data;
	struct Stacknode* next;
} STACKNODE;
typedef struct Stack
{
	STACKNODE* top;
} STACK;
void initStack(STACK* stack)
{
	stack->top = NULL;
}
STACKNODE* createStackNode(int value)
{
	STACKNODE* newnode = (STACKNODE*)malloc(sizeof(STACKNODE));
	newnode->data = value;
	newnode->next = NULL;
	return newnode;
}
int isStackEmpty(STACK* stack)
{
	return stack->top == NULL;
}
void push(STACK* stack, int value)
{
	STACKNODE* newnode = createStackNode(value);
	newnode->next = stack->top;
	stack->top = newnode;
}
int pop(STACK* stack)
{
	if(isStackEmpty(stack))
	{
		printf("Stack is empty!. Can not pop.\n");
		return -1;
	}
	STACKNODE* temp = stack->top;
	int data = temp->data;
	stack->top = temp->next;
	free(temp);
	return data;
}
int main()
{
	STACK stack;
	initStack(&stack);
	push(&stack, 10);
	push(&stack, 20);
	push(&stack, 30);
	push(&stack, 40);
	push(&stack, 50);
	int data = pop(&stack);
	printf("Pooped element is: %d\n", data);
	return 0;
}

