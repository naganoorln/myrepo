#include <stdio.h>
#include <string.h>
void replaceSubString(char* str, const char* oldstr, const char* newstr)
{
    char buffer[1024];
    int oldstrlen = strlen(oldstr);
    char* pos;
    buffer[0] = '\0';
    char* start = str;
    while((pos = strstr(start, oldstr)) != NULL)
    {
        strncat(buffer, start, pos - start);
        strcat(buffer, newstr);
        start = pos + oldstrlen;
    }
    strcat(buffer, start);
    strcpy(str, buffer);
}
int main()
{
    char str[1024] = "Hellow world, wellcome to the world of c programming.";
    replaceSubString(str, "world", "universe");
    printf("Result: %s\n",str);
    return 0;
}