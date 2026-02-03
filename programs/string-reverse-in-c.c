#include <stdio.h>
#include <string.h>
void reverseString(char* str)
{
    //int end = strlen(str) - 1;
    int end = 0;
    int i = 0;
    while(str[i])    {
        i++;
        end++;
    }
    end--;
    int start = 0;
    while(start <= end) /* < only not required <= */
    {
        char temp;
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
int main()
{
    char str[] = "hello world";
    reverseString(str);
    printf("%s\n",str);
    return 0;
}