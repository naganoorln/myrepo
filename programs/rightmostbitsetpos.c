#include <stdio.h>
int main() {
    unsigned int n = 18; // 10010
    int pos = 0;
    while (!(n & 1)) {
        n >>= 1;
        pos++;
    }
    printf("Rightmost set bit position: %d\n", pos);
    return 0;
}

