#include <stdio.h>
#include <string.h>
typedef int (*funptr)(int, int);

int add(int data1, int data2)
{
	return data1 + data2;
}
int sub(int data1, int data2)
{
	return data1 - data2;
}
int multify(int data1, int data2)
{
	return data1 * data2;
}
int divide(int data1, int data2)
{
	return data1 / data2;
}

int callback(funptr fptr, int d1, int d2)
{
	return fptr(d1,d2);
}
int main()
{
        char str[10];
        int result;
        printf("Enter the opeartion:");
        scanf("%s", str);
        printf("%s\n",str);
        if(!strcmp(str, "add"))
        {
            result = callback(add, 10, 20);
        } else if(!strcmp(str, "sub"))
        {
            result = callback(sub,30 , 20);
        } else if(!strcmp(str, "multify"))
        {
            result = callback(multify, 10, 20);
        } else if(!strcmp(str, "divide"))
        {
            result = callback(divide, 40, 20);
        } else {
            printf("Invalid operation...!\n");
            return 0;
        }
	    printf("%d\n", result);
	    return 0;
}
