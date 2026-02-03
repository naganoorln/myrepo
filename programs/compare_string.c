#include <stdio.h>
/* Compare String */
int compareString(const char* str1, const char* str2)
{
    while(*str1 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return *((char*)str1) - *((char*)str2);
}
int main()
{
    char str1[] = "Hello";
    char str2[] = "Window";
    printf("%d\n", compareString(str1, str2));
    return 0;
}