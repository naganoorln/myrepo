#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int * b;
    b = (int*) malloc (1);
    *b=110000;
    printf("%d\n", *b);
    free (b);
    return 0;
}
