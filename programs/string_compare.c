#include <stdio.h>
#include <string.h>
int compstr(const char* str1, const char* str2)
{
    while(*str1 != '\0' && *str2 != '\0')
    {
        if(*str1 != *str2)
        {
            return (unsigned char)(*str1) - (unsigned char)(*str2);
            
        }
        str1++;
        str2++;
    }   
    return (unsigned char)(*str1) - (unsigned char)(*str2);
}
int main()
{
    const char* str1 = "Hello";
    const char *str2 = "Hello";
    const char* str3 = "Hell";
    const char* str4 = "world!";
    printf("%d\n",strcmp(str1,str2));
    printf("%d\n",compstr(str1, str2));
    printf("%d\n",strcmp(str1,str3));
    printf("%d\n",compstr(str1, str3));
    printf("%d\n",strcmp(str1,str4));
    printf("%d\n",compstr(str1, str4));
    printf("%d\n",strcmp(str3,str1));
    printf("%d\n",compstr(str3, str1));    ;
    printf("%d\n",strcmp(str4,str3));
    printf("%d\n",compstr(str4, str3));
    return 0;
    
}
