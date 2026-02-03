#include <stdio.h>
#define MAX 10
int stack[MAX];
int top = -1;

int isStackFull()
{
	return top == (MAX - 1);
}

int isStackEmpty()
{
	return top == -1;
}

void push(int data)
{
	if(isStackFull())
	{
		printf("Stack is full.\n");
		return;
	}
	stack[++top] = data;
}

int pop()
{
	if(isStackEmpty())
	{
		printf("Stack is empty.\n");
		return -1;
	}
	return stack[top--];
}

void printStack()
{	
	if(!isStackEmpty())
	{
		for(int i = top; i >= 0; i--)
			printf("%d ", stack[i]);
		printf("\n");
	}
}

int main()
{
	push(10);
	push(20);
	push(30);
	push(40);
	push(50);
	push(60);
	push(70);
	push(80);
	push(90);
	push(100);
	push(110);
	printf("Stack:");
	printStack();
	printf("Pop:%d", pop());
        printf("\nStack:");
	printStack();
	printf("Pop:%d", pop());
        printf("\nStack:");
        printStack();
	return 0;
}


