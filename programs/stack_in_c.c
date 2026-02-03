/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/* Stack Implimentaion */
#include <stdio.h>
#define MAX 5
int stack[MAX];
int top = -1;
int isStackFull()
{
    return (top == (MAX - 1));
}

int isStackEmpty()
{
    return (top == -1);
}

void push(int num)
{
    if(isStackFull())
    {
        printf("Can not push element %d. The stack is full\n",num);
    } else {
        stack[++top] = num;
        printf("Element %d pushed\n",num);
    }
}
int pop()
{
    if(isStackEmpty())
    {
        printf("Stack is empty\n");
    } else {
        return stack[top--];
    }
}
void displayStack()
{
    if(isStackEmpty())
    {
        printf("Stack is empty\n");
    } else {
        for(int i = top; i >= 0; i--)
        {
            printf("%d \n",stack[i]);
        }
    }
}
int main()
{
    
   push(10);
   push(12);
   push(13);
   push(14);
   push(15);
   displayStack();
   pop();
   push(16);
   displayStack();
   pop();
   displayStack();
   return 0;
}
