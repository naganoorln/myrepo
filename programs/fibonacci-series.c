#include <stdio.h>
#include <stdlib.h>
int fibonacci(int n)
{
    if(n <= 1)
    {
        return n;
    }
    return fibonacci(n -1) + fibonacci(n - 2);
}
int main()
{
    int n;
    while(1)
    {
        printf("Enter number: ");
        scanf("%d", &n);
        if(n == 0)
        {
            exit(1);
        }
        printf("Fibonacci Series: ");
        for(int i = 1; i <= n; i++)
        {
            printf("%d ", fibonacci(i));
        }
        printf("\n");
    }
    return 0;
}

