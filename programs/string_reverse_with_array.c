/* String reverse */
#include <stdio.h>
#include <string.h>
void reverseString(char* str)
{
    int start = 0;
    int end = strlen(str) - 1;
    while(start < end)
    {
        int temp = str[start];
        str[start] = str[end];
        str[end] = temp;
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