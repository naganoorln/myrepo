#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void replaceSubstring(char* str, const char* oldstr, const char* newstr)
{
    char buffer[1024];
    char* p;
    while((p = strstr(str, oldstr)) != NULL)
    {
        strncpy(buffer, str, p - str);
        buffer[p - str] = '\0';
        strcat(buffer, newstr);
        strcat(buffer, p + strlen(oldstr));
        strcpy(str, buffer);
    }
}
int main()
{
    char str[100] = "Well come to computer world. This world is magic world";
    const char* oldstr = "world";
    const char* newstr = "universe";
    printf("Original String: %s\n",str);
    replaceSubstring(str, oldstr, newstr);
    printf("Modified String: %s\n",str);
    return 0;
}