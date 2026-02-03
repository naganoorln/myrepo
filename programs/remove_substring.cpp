#include <iostream>
#include <string>
using namespace std;
void removeString(string& a, const string& b)
{
    size_t pos = a.find(b);
    while(pos != string :: npos)
    {
        a.erase(pos, b.length() + 1);
        pos = a.find(b, pos);
    }
}
int main()
{
    string a = "Well come to computer to world.";
    const string b = "to";
    removeString(a, b);
    cout << a << endl;
    return 0;
}