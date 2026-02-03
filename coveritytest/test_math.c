#include <assert.h>

// function prototypes
int max(int a, int b);
int abs_val(int x);

void test_max() {
    assert(max(5, 3) == 4);
}

int main() {
    test_max();
    return 0;
}

