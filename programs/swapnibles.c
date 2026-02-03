
#include <stdio.h>

#include <stdio.h>
/* Function to swap upper and lower 4 bits (nibbles) */
unsigned char swap_nibbles(unsigned char byte)
{
    unsigned char f1 = ((byte >> 4) & 0x0F);  /* high nibble -> low */
    unsigned char f2 = ((byte << 4) & 0xF0);  /* low nibble -> high */
    return (f1 | f2);                         /* combine */
}

int main()
{
    unsigned char byte;
    byte = 5;
    unsigned char result = swap_nibbles(byte);
    printf("Original byte : 0x%02X\n", byte);
    printf("After swap    : 0x%02X\n", result);
    printf("Original byte : %b\n", byte);
    printf("After swap    : %b\n", result);
    return 0;
}
