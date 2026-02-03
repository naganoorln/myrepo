/* callback function example */
#include <stdio.h>
typedef int (*callBackFun)(int, int);
int add(int num1, int num2)
{
    return num1 + num2;
}
int multify(int num1, int num2)
{
    return num1 * num2;
}
int functionCallback(callBackFun cbf, int num1, int num2)
{
    return cbf(num1, num2);
}
int main()
{
    printf("%d\n",functionCallback(add, 10, 12));
    printf("%d\n",functionCallback(multify, 10, 12));
    return 0;
}