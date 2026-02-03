/* Reverse array using pointer airthmetics */
#include <stdio.h>
void reverseArray(int* arr, int size)
{
    int* start = arr;
    int* end = start + size - 1;
    int temp;
    while(start < end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
int main()
{
    int arr[] = {4, 6, 8, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    reverseArray(arr, n);
    for(int i = 0; i < n; i ++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}