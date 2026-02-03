#include <stdio.h>
int main()
{
    union 
    {
        unsigned int num;
        unsigned char bytes[4];
    }endianCheck;
    endianCheck.num = 1;
    if(endianCheck.bytes[0])
    {
        printf("Little endian.\n");
    } else {
        printf("Big endian.\n");
    }
    return 0;
}