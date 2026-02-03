#include <stdio.h>
#include <string.h>
void stringReverse(char* str)
{
    //int start = 0;
    //int end = strlen(str) -1;
    char* start = str;
    char* end = str + strlen(str) - 1;
    /*while(start < end)
    {
        int temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }*/
    while(start < end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
int main()
{
    char str[] ="hello world";
    stringReverse(str);
    printf("%s\n", str);
    return 0;
}