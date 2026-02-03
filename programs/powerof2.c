#include <stdio.h>
int main() {
    unsigned int n = 4;
    if (n && !(n & (n - 1)))
        printf("%u is power of 2\n", n);
    else
        printf("%u is not power of 2\n", n);
    return 0;
}

