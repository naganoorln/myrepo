#include <stdio.h>
int main()
{
    int count = 0;
    int num = 6;
    while(num )
    {
        count++;
        num &= (num - 1);
    }
    printf("Bit Count: %d\n",count);
    return 0;
}
