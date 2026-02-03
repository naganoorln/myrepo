/* Reverse string */
#include <stdio.h>
#include <string.h>
void reverseString(char* str)
{
    char* start = str;
    char* end = str + strlen(str) -1;
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
    char str[] = "Window";
    reverseString(str);
    printf("%s\n", str);
    return 0;
}