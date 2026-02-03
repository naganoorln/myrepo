#include <iostream>
#include <thread>
#include <condition_variable>
using namespace std;
#define MAX 20
mutex mtx;
condition_variable oddv,evenv;
bool isNumEven = true, isNumOdd = false;
int num = 0;
void even()
{
    while(num <= MAX)
    {
        unique_lock<mutex> lock(mtx);
        evenv.wait(lock, [] {return num % 10 == 0;});
        if(num <= MAX)
        {
            cout << "Even Num: " << num << endl;
            num++;
            isNumOdd = true;
            isNumEven = false;
            lock.unlock();
            oddv.notify_one();
        }
    }
}
void odd()
{
    while(num <= MAX)
    {
        unique_lock<mutex> lock(mtx);
        oddv.wait(lock, [] {return num % 10 != 0;});
        if(num <= MAX)
        {
            cout << "Odd Num: " << num << endl;
            num++;
            isNumEven = true;
            isNumOdd = false;
            lock.unlock();
            evenv.notify_one();
        }
    }
}
int main()
{
    thread event(even);
    thread oddt(odd);
    event.join();
    oddt.join();
    return 0;
}
