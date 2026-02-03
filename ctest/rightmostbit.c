#include <stdio.h>
int main()
{
	unsigned int num = 6;
	int pos = 0;
	while(!(num & 1))
	{
        	num >>= 1;
		pos++;
	}
	printf("Rightmost bit set is %d\n", pos);
	return 0;
}
