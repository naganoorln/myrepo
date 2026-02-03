#include <stdio.h>
void mtpp(int **ptp, int x, int *ax) 
{
    *ax =100;
    **ptp = 101;
    x = 102;
}

int main() 
{
    int x = 10;
    int *p = &x;
    int **pp = &p;
    printf("Value of x: %d\n", x);
    mtpp(pp, x, &x);
    printf("Value of x  %d\n", x);
    return 0;
}

