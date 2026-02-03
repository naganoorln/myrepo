#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#define MAX 20
using namespace std;
mutex mtx;
condition_variable oddv, evenv;
int num = 0;
void even()
{
    while(num <= MAX)
    {
        unique_lock<mutex> lock(mtx);
        evenv.wait(lock, [] {return num % 2 == 0;});
        if(num <= MAX)
        {
            cout << "Even Num :  " << num << endl;
            num++;
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
        oddv.wait(lock, [] {return num % 2 != 0;});
        if(num <= MAX)
        {
            cout << "Odd Num  :  " << num << endl;
            num++;
            lock.unlock();
            evenv.notify_one();
        }        
    }
}
int main()
{
    thread oddthd(odd);  
    thread eventhd(even);
    oddthd.join();
    eventhd.join();
    return 0;
}