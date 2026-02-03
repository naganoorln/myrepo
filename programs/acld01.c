#include <stdlib.h>
#include <stdio.h>
int * func() 
{
    int *pi;
    for (int i = 0; i < 100; i++)
    {
        pi = malloc(100);
    }
    return pi;
}

int main() 
{
    int * i = func();
    *i = 100;

// print *i ?
printf("%d\n", *i);
free(i);
    return 0;
}
