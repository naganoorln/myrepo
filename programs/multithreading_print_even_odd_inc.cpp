#include <iostream>
#include <thread>
#include <mutex>
#define MAX_NUM 20
using namespace std;
mutex mtx;
int num = 1;
void printOddEvenNumbers(bool is_number_even)
{
    while(true)
    {
        {
            lock_guard<mutex> lock(mtx);
            if(num > MAX_NUM)
                break;
            if((num % 2 == 0 && is_number_even) || num % 2 != 0 && !is_number_even)
            {
                cout << (is_number_even? "Even number: " : "Odd number: " ) << num << endl;
                num++;
            }
        }
    }
}
int main()
{
    thread even_thread(printOddEvenNumbers, true);
    thread odd_thread(printOddEvenNumbers, false);
    even_thread.join();
    odd_thread.join();
    return 0;
}
