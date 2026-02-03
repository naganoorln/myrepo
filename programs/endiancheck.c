/* Endian checking */
#include <stdio.h>
int main()
{
	unsigned int num = 1;
	unsigned char* c = (unsigned char*)&num;
	if(*c)
	{
		printf("Little Endian\n");
	} else {
		printf("Big Endian\n");
	}
	return 0;
}