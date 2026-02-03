// C program to reverse every sub-arry formed by consecutive k elements
#include <stdio.h>
void reverseArryInGroups(int arr[], int n, int k)
{
    for(int i = 0; i < n; i += k)
    {
        int left = i;
        int right = i + k - 1 < n -1 ? i + k - 1 : n - 1;
        while(left < right)
        {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Arry before reverse:");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    reverseArryInGroups(arr, n, k);
    printf("Arry after reverse:");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}