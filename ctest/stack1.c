#include <stdio.h>
#define MAX 5
int top = -1;
int stack[MAX];

int isFull()
{
	return top == (MAX - 1);
}
int isEmpty()
{
	return top == -1;
}
void push(int value)
{
	if(isFull())
	{
		printf("Stack is full.\n");
		return;
	}
	stack[++top] = value;
}
int pop()
{
	if(isEmpty())
	{
		printf("Stack is empty.\n");
		return -1;
	}
	return stack[top--];
}
void disply()
{
	if(isEmpty)
	{
		for(int i = top; i >= 0; i--)
			printf("%d ", stack[i]);
	}
	printf("\n");
}

int main()
{
	push(10);
	push(20);
	push(30);
	push(40);
	push(50);
	push(60);
	disply();
	return 0;
}	

