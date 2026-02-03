/* Reverse bits of a number */
#include <stdio.h>
unsigned int reverseBits(unsigned int num)
{
	int numofbits = sizeof(num) * 8;
    	unsigned int reversed = 0;
    	for(int i = 0; i < numofbits; i++)
    	{
        	reversed = (reversed << 1) | (num & 1);
    		num >>= 1;
    	}
    	return reversed;
}
int main()
{
	unsigned int num = 20;
	unsigned int reversed;
	printf("Number before reverse: %d:%b\n",num, num);
	reversed = reverseBits(num);
	printf("Number after reverse: %d:%b\n", reversed, reversed);
        return 0;
}

