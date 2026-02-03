#include <stdio.h>
int main() {
    int *p = (int*)0xA;
    printf("%p\n", p);
    printf("%d\n", *p);
    return 0;
}
