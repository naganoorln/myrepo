#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define CHAR_COUNT 256
// Function to check If two strings are anagrams
bool areAnagrams(char str1[], char str2[])
{
    if(strlen(str1) != strlen(str2))
    {
        return false;
    }
    int count[CHAR_COUNT] = {0};
    for(int i = 0; i < strlen(str1); i++)
    {
        count[(int)str1[i]]++;
        count[(int)str2[i]]--;
    }
    for(int i = 0; i < CHAR_COUNT; i++)
    {
        if(count[i] != 0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    char str1[100], str2[100];
    printf("Enter first string: ");
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);
    if(areAnagrams(str1, str2))
    {
        printf("The strings are anagrams.\n");
    } else {
        printf("The strings are not areAnagrams.\n");
    }
    return 0;
}