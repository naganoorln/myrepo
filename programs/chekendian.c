/* Endian checking */
#include<stdio.h>
int main()
{
	union
	{
		unsigned int num;
		unsigned char bytes[4];
	}EndianChecking;
	EndianChecking.num = 1;
	if(EndianChecking.bytes[0])
	{
		printf("Little Endian\n");
	} else {
		printf("Big Endian\n");
	}
	return 0;
}