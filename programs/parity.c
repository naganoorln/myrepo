#include <stdio.h>
int main()
{
    unsigned int num = 3;
    int parity = 0;
    while(num)
    {
        parity = !parity;
        num &= (num -1);
    }
    printf("parity: %s\n", parity ? "odd" : "even");
    return 0;
}