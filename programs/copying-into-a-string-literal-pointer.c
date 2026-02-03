/* Copying into a string literal pointer */
#include <stdio.h>
#include <string.h>
int main()
{
    char* dest = "Hello";
    strcpy(dest, "Words");
    return 0;
}