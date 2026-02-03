#include <stdio.h>
int swapBit(unsigned int num, int n, int m)
{
    unsigned int bit_n = (num >> n) & 1;
    unsigned int bit_m = (num >> m) & 1;
    if(bit_n != bit_m)
    {
         num ^= (1 << n);
         num ^= (1 << m);
        /*if(bit_n == 1)
        {
            num &= ~(1 << n);
            num |= (1 << m);
        } else {
            num &= ~(1 << m);
            num |= (1 << n);
        }*/
    }
    return num;
}

int main()
{
    printf("%d\n",swapBit(3, 1, 2));
    return 0;
}