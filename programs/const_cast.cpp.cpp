#include <iostream>
using namespace std;

void printValue(int* x) {
    *x = 50;
    cout << *x << endl;
}

int main() {
    const int a = 10;
    int* b = const_cast<int*>(&a);
    *b = 50;
    cout << *b << endl;
    printValue(const_cast<int*>(&a));  // remove const
    return 0;
}
