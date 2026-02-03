#include <stdio.h>
int main() 
{
    int a = 10;
    int *p = &a;
    printf("Value of a, p and *p: %d  %d %d\n", a , p, *p);
    p = p + 1040;
    *p = 50;      
    printf("Value of a, p and *p: %d %d %d\n", a , p, *p);
    return 0;
}
