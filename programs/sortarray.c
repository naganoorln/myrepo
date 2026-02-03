#include <stdio.h>
void sortArray(int arr[], int size)
{
    int temp ;
   for(int i = 0; i < size; i++) 
   {
       for(int j = i + 1; j < size; j++)
       {
           if(arr[i] > arr[j])
           {
               temp = arr[i];
               arr[i] = arr[j];
               arr[j] = temp;
           }
       }
   }
}
int main()
{
    int arr[] = {6, 9, 5, 7, 2, 8, 1, 4, 10, 3};
    int size = sizeof(arr)/sizeof(arr[0]);
    sortArray(arr, size);
    for(int i = 0; i < size; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}