#include <stdio.h>
int replaceDigit0As1AndDigit1As0OfNumber(int n)
{
    int rnum = 0;
    int mnum = 0;
    int digit;
    while(n)
    {
        digit = n % 10;
        if(digit == 0)
        {
            digit = 1;
        } else if(digit == 1) {
            digit = 0;
        }
        rnum = rnum * 10 + digit;
        n /= 10;
    }
    while(rnum)
    {
        mnum = mnum * 10 + (rnum % 10);
        rnum /= 10;
    }
    return mnum;
}

int main()
{
    int n = 211167;
    int newnum = replaceDigit0As1AndDigit1As0OfNumber(n);
    printf("%d\n",newnum);
    return 0;
}