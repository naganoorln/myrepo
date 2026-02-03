#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
/* Thread function to calculate sum of digits in a string */
void* sumOfDigitsOfString(void* arg)
{
    char* str = (char*)arg;
    int* sum = malloc(sizeof(int));
    if(sum == NULL)
    {
        perror("Failed to allocate memory");
        pthread_exit(NULL);
    }
    *sum = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if(isdigit((unsigned char)str[i]))
        {
            *sum += str[i] - '0';
        }
    }
    pthread_exit((void*)sum);
}
/* If string contains more vovels than consonents,call it as good string otherwise bad string.
   Thread function check string is good or bad if good string return 1 otherwise 0 */
   void* checkGoodOrBadString(void* arg)
   {
       int vovels = 0;
       int consonents = 0;
       char ch;
       char* str = (char*)arg;
       int* result = malloc(sizeof(int));
       for(int i = 0; str[i] != '\0'; i++)
       {
           ch = tolower(str[i]);
           if(isalpha(ch))
           {
                if(ch == 'a' ||
                ch == 'e' || 
                ch == 'i' || 
                ch == 'o' ||
                ch == 'u')
                {
                    vovels++;
                } else {
                    consonents++;
                }
           }
       }
       *result = vovels > consonents ? 1 : 0;
       pthread_exit((void*)result);
   }
int main()
{
    pthread_t thread1, thread2;
    char input[100];// = "56hh 98hh";
    printf("Enter an alphanumeric string: ");
    //scanf("%s", input);
    fgets(input, sizeof(input), stdin);
    if(pthread_create(&thread1, NULL, sumOfDigitsOfString, (void*)input) != 0)
    {
        perror("Failed to create thread");
        return 1;
    }
    if(pthread_create(&thread2, NULL, checkGoodOrBadString, (void*)input) != 0)
    {
        perror("Failed to create thread");
        return 1;
    }
    void* result1;
    if(pthread_join(thread1, &result1) != 0)
    {
        perror("Failed to join thread");
        return 1;
    }
    void* result2;
    if(pthread_join(thread2, &result2) != 0)
    {
        perror("Failed to join thread");
        return 1;
    }
    int sum = *(int*)result1;
    printf("Sum of digits in the string: %d\n", sum);
    free(result1);
    int check = *(int*)result2;
    if(check)
    {
        printf("Good string\n");
    }else {
        printf("Bad string\n");
    }
    return 0;
}
