#include <stdio.h>
unsigned int toggleNumber(unsigned int num, int index1, int index2)
{
    num ^= (1 << index1);
    num ^= (1 << index2);
    return num;
}
int main()
{
    unsigned int num = toggleNumber(10, 0, 2);
    printf("%d\n",num);
    
}