#include <stdio.h>
int findSecondLargestInAnArray(int arr[], int n)
{
    int secondlargest = arr[0], largest = arr[1];
    if(secondlargest > largest)
    {
        int temp = secondlargest;
        secondlargest = largest;
        largest = temp;
    }
       
    for(int i = 2; i < n; i++)
    {
        if(arr[i] > largest)
        {
            secondlargest = largest;
            largest = arr[i];
        } else if(arr[i] < largest && arr[i] > secondlargest) {
            secondlargest = arr[i];
        }           
    }
    return secondlargest;
}
int main()
{
    int arr[5] = {93, 69, 77, 17, 65};
    int size = sizeof(arr)/sizeof(arr[0]);
    int sl = findSecondLargestInAnArray(arr, size);
    printf("Second largest: %d\n", sl);
    return 0;
}