#include <stdio.h>
// function to count bits of a number
unsigned int countBits(unsigned int num)
{
    unsigned int count = 0;
    while(num)
    {
        count += (num & 1);
        num >>= 1;
    }
    return count;
}
int main()
{
    unsigned int num;
    printf("Enter the number: ");
    scanf("%u", &num);
    printf("Bit Counts: %u\n",countBits(num));
    return 0;
}