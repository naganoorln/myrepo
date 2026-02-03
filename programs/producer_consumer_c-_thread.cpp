/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>

using namespace std;
queue<int> buffer;
const unsigned int max_buffer_size = 10;
mutex mtx;
condition_variable queue_full;
condition_variable queue_empty;

void producer()
{
    int item = 0;
    while(true)
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        unique_lock<mutex> lock(mtx);
        queue_full.wait(lock, []{return buffer.size() < max_buffer_size;});
        buffer.push(item++);
        cout << item - 1 << " is produced" << endl;
        lock.unlock();
        queue_empty.notify_one();
    }
}

void consumer()
{
    int item = 0;
    while(true)
    {
        this_thread::sleep_for(chrono::milliseconds(15));
        unique_lock<mutex> lock(mtx);
        queue_empty.wait(lock, []{return !buffer.empty();});
        item = buffer.front();
        buffer.pop();
        cout << item << " is consumed" << endl;
        lock.unlock();
        queue_full.notify_one();
    }
}

int main()
{
    thread producer_thread(producer);
    thread consumer_thread(consumer);
    producer_thread.join();
    consumer_thread.join();
    return 0;
}