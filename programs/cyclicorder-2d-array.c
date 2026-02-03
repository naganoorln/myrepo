#include <stdio.h>

int main() {
    int a[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12}
    };

    int top = 0, bottom = 2;
    int left = 0, right = 3;
    int i;

    while (top <= bottom && left <= right) {

        for (i = left; i <= right; i++)
            printf("%d ", a[top][i]);
        top++;

        for (i = top; i <= bottom; i++)
            printf("%d ", a[i][right]);
        right--;

        if (top <= bottom) {
            for (i = right; i >= left; i--)
                printf("%d ", a[bottom][i]);
            bottom--;
        }

        if (left <= right) {
            for (i = bottom; i >= top; i--)
                printf("%d ", a[i][left]);
            left++;
        }
    }
    printf("\n");

    return 0;
}
