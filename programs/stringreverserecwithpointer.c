#include <stdio.h>
#include <string.h>

void reverse(char *str, char* stre) 
{
    if (str >= stre) 
        return;
    char temp = *str;
    *str = *stre;
    *stre = temp;
    reverse(++str, --stre);
}
int main() {
    char str[] = "hello";
    char* stre = str + (strlen(str) - 1);
    reverse(str, stre);
    printf("%s\n", str);
    return 0;
}