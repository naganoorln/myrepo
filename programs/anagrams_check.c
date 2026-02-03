#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void sort(char str[])
{
    int len = strlen(str);
    char temp;
    for(int i = 0; i < len - 1; i++)
    {
        for(int j = i + 1; j < len; j++)
        {
            if(str[i] > str[j])
            {
                // swap characters
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}
bool areStringsAnagrams(char str1[], char str2[])
{
    if(strlen(str1) != strlen(str2))
    {
        return false;
    }
    int l1 = strlen(str1) - 1;
    int l2 = strlen(str2) - 1;
    sort(str1);
    sort(str2);
    if(strcmp(str1,str2) != 0)
    {
        return false;
    }
    return true;
}
int main()
{
    char str1[100], str2[100];
    printf("Enter the first string: ");
    scanf("%s", str1);
    printf("Enter the second string: ");
    scanf("%s", str2);
    if(areStringsAnagrams(str1, str2))
    {
        printf("The strings are anagrams.\n");
    }else {
        printf("The string are not anagrams.\n");
    }
    return 0;
}