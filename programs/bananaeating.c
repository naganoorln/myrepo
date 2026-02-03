#include <stdio.h>
int canEatAllBananas(int piles[], int n, int k, int h)
{
    int hours = 0;
    for(int i = 0; i < n; i++)
    {
        hours += (piles[i] + k -1) / k;
    }
    return hours <= h;
}
int minEatingSpeed(int piles[], int n, int h)
{
    int left = 1, right = 0;
    for(int i = 0; i < n; i++)
    {
        if(piles[i] > left)
        {
            right = piles[i];
        }
    }
    while(left < right)
    {
        int mid = left + (right - left)/2;
        if(canEatAllBananas(piles, n, mid, h))
        {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
int main()
{
    int piles[] = {3, 6, 7, 11};
    int n = sizeof(piles) / sizeof(piles[0]);
    int h = 8;
    int result = minEatingSpeed(piles, n, h);
    printf("Minimum speed Koko can eat the bananas: %d\n",result);
    return 0;
}
