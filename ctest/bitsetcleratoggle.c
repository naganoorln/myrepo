#include <stdio.h>
int main()
{
	unsigned int num = 0b00001010; /* 10 in binary */
	int bit = 2;
	printf("Original: %u\n",num);
	printf("Set/Clear/Toggle bit 2\n");
	num = num | (1 << bit); /* bit set */
	printf("After set: %u\n", num);
	num = num & ~(1 << bit); /* bit clear */
	printf("After clear: %u\n", num);
	num = num ^ (1 << bit); /* bit toggle */
	printf("After Toggle: %u\n", num);
	return 0;
}
				      

