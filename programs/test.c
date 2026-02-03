#include <stdio.h>
int main()
{
    int a = 5; int *p = &a; int **r = &p;
    *r = NULL;
    printf("%d", *p);
    return 0;
}