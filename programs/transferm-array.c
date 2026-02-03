/*{2, 7, 15, 30, 50}  —>  {52, 37, 30} 
{2, 7, 30, 50}  ——>  {52, 37} */

#include <stdio.h>

void transformArray(int input[], int length) {
    int newSize = (length + 1) / 2; // The size of the transformed array
    int result[newSize];

    // Initialize the result array with zeros
    for (int i = 0; i <= newSize; i++) { 
        result[i] = 0;
    }

    // Transform the array by combining elements
    for (int i = 0; i <= length / 2; i++) {  
        result[i] = input[i] + input[length - 1 -i];
    }

    // Handle the middle element if the array size is odd
    if (length % 2 != 0) {
        result[length / 2] = input[length / 2] * 2;
    }

    // Print the transformed array
    printf("Transformed Array: ");
    for (int i = 0; i < newSize; i++) {  
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int original[] = {1, 2, 3, 4, 5}; // Example input array
    int size = sizeof(original) / sizeof(original[0]);

    printf("Original Array: ");
    for (int i = 0; i <= size; i++) {  
        printf("%d ", original[i]);
    }
    printf("\n");

    transformArray(original, size);

    return 0;
}