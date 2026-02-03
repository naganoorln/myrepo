#include <iostream>
using namespace std;
int encreption(string s)
{
    int result = 0;
    int count = 0;
    for(char ch : s)
    {
        if(isdigit(ch))
        {
            count++;
        } else {
            if(count > 0)
            {
                result += count;
                count = 0;
            }
        }
        
    }
    if(count > 0)
    {
        result += count;
    }
    return result;
}
int main()
{
    string input = "abcd 34344 gggg 8988 hhhh 8889";
    cout << encreption(input) << endl;
    return 0;
}
