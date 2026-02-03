/*Swap bits */
#include <stdio.h>
unsigned int swapBits(unsigned int num, int m, int n)
{
unsigned int bit_m = (num >> m) & 1;
unsigned int bit_n = (num >> n) & 1;
if(bit_m != bit_n)
{
	num ^= (1 << m);
	num ^= (1 << n);
}
return num;
}
int main()
{
	unsigned int num = 5;
	unsigned int mnum = swapBits(num, 1, 2);
	printf("Number after bit swap: %d\n", mnum);
	return 0;
}
