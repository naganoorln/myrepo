/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/* Reverse Bits of A number */
#include <stdio.h>
unsigned int reverseBits(unsigned int num)
{
    int numBits = sizeof(num) * 8;
    unsigned int reversed = 0;
    for(int i = 0; i < numBits; i++)
    {
        reversed = (reversed << 1) | (num & 1);
        num >>= 1;
    }
    return reversed;
}

int main()
{
    unsigned int num = 7;
    printf("Oiginal number is: %u\n",num);
    unsigned int reversed = reverseBits(num);
    printf("Reversed number is: %u\n",reversed);
    return 0;
}

