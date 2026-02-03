/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/* Program to replace a word by new word in a string */
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
void replaceWordByNewWordInString(char* original, char* oldword, char* newword)
{
    char* pos;
    char temp[1000];
    int index = 0;
    int owln;
    owln = strlen(oldword);
    while((pos = strstr(original, oldword)) != NULL)
    {
        strcpy(temp, original);
        index = pos - original;
        original[index] = '\0';
        strcat(original, newword);
        strcat(original, temp + index + owln);
    }
}

int main()
{
    char str[] = "xxforxx xx for xx";
    char oldw[] = "xx";
    char neww[] = "Geeks";
    printf("Origial string: %s\n",str);
    replaceWordByNewWordInString(str,oldw,neww);
    printf("Modified string: %s\n",str);
    return 0;
}