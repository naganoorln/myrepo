/* To find the pair of array elements where sum of pairs is equal to given number say k */
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
struct Pairs
{
    int first;
    int second;
};

struct Pairs* findPairs(int arr[], int k, int size, int* paircount)
{
    struct Pairs *result = NULL;
    int present[MAX_SIZE];
    int count = 0;
    for(int i = 0; i < size; ++i)
    {
        int complement = k - arr[i];
        if(complement >= 0 && present[complement])
        {
            
                (*paircount)++;
                result = (struct Pairs*)realloc(result, *paircount * sizeof(struct Pairs));
                result[count].first = arr[i];
                result[count].second = complement;
                count++;
        }
        present[arr[i]] = 1;
    }
    
    return result;
}

int main()
{
    int arr[] = {1, 4, 5, 7, 3, 8, 9};
    int paircount = 0;
    int k = 13;
    int size = sizeof(arr) / sizeof(arr[0]);
    struct Pairs* pairs = findPairs(arr, k, size, &paircount);
    printf("Pair count: %d\n",paircount);
    printf("Pairs are\n");
    for(int i = 0; i < paircount; i++)
    {
        printf("%d + %d = %d\n",pairs[i].first, pairs[i].second, k);
    }
    return 0;
}