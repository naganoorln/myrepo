#include <iostream>
#include <vector>
using namespace std;
class A
{
    private:
        int b;
        virtual void func() {}
        char m;
};
int main()
{
    vector<int> v;
    cout << sizeof(A) << endl;
    cout << v.size() << endl;
    return 0;
}