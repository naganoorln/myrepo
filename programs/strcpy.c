/* String copy */
#include <stdio.h>
char* stringCopy(char* dest, const char* src)
{
    char* ptr = dest;
    while(*src != '\0')
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}
int main()
{
    char dest[10];
    const char src[] = "Hello";
    printf("%s\n", stringCopy(dest, src));
    printf("%s\n",dest);
    return 0;
}