#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Pair
{
	int first;
	int second;
} ARRAYPAIRS;
ARRAYPAIRS* findPairs(int arr[], int size, int target, int* paircount)
{
	ARRAYPAIRS* pairs = NULL;
	int present[MAX] = {0};
	for(int i = 0; i < size; i++)
	{
		int complement = target - arr[i];
		if(complement >= 0 && present[complement])
		{
			pairs = (ARRAYPAIRS*)realloc(pairs, (*paircount) * sizeof(ARRAYPAIRS));
			pairs[*paircount].first = complement;
			pairs[*paircount].second = arr[i];
			(*paircount)++;
		}
		present[arr[i]] = 1;
	}
	return pairs;
}
int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	int size = sizeof(arr)/sizeof(arr[0]);
	int target = 8;
	int paircount = 0;
	ARRAYPAIRS* pair = findPairs(arr, size, target, &paircount);
	printf("Pairs are\n");
	if(paircount == 0)
	{
		printf("No pairs\n");
		return 0;
	}
	for(int i = 0; i < paircount; i++)
	{
		printf("%d + %d = %d\n", pair[i].first, pair[i].second, target);
	}
	return 0;
}