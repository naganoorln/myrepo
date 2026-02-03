#include <stdio.h>
void reverseArray(int array[], int start, int end)
{
	int temp;
	while(start < end)
	{
		temp = array[start];
		array[start] = array[end];
		array[end] = temp;
		start++;
		end--;
	}
}
void printArray(int array[], int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}
int main()
{
	int array[] = {1,2,3,4,5,6,7,8};
	int size = sizeof(array)/sizeof(array[0]);
	printArray(array, size);
	reverseArray(array, 0, size -1);
	printArray(array, size);
	return 0;
}