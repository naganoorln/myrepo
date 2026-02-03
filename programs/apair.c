/* To find the pair of arry elements where sum of pairs is equal to a given number say k */
#include <stdio.h>
#include <stdlib.h>
#define MAX_COUNT 100
struct pairs
{
    int first;
    int second;
};
struct pairs* findPair(int arr[], int size, int k, int* paircount)
{
    struct pairs* result = NULL;
    int present[MAX_COUNT] = {0};
    int count = 0;
    for(int i = 0; i < size; i++)
    {
        int complement = k - arr[i];
        if(complement >= 0 && present[complement])
        {
            (*paircount)++;
            result = (struct pairs*)realloc( result, *paircount * sizeof(struct pairs));
            result[count].first = complement;
            result[count].second = arr[i];
            count++;
        }
        present[arr[i]] = 1;
    }
    return result;
}
int main()
{
    int arr[] = {2, 4, 7, 9, 11, 23, 44};
    int paircount = 0;
    int k = 13;
    int size = sizeof(arr)/sizeof(arr[0]);
    struct pairs* result = findPair(arr, size, k, &paircount);
    printf("Pair Count: %d\n", paircount);
	printf("Pairs are\n");
    for(int i = 0; i < paircount; i++)
    {
        printf("%d + %d = %d\n",result[i].first, result[i].second, k);
    }
    return 0;   
 }