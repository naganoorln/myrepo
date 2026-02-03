#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
using namespace std;
class Singleton
{
    private:
        static Singleton* sobj;
        static mutex mtx;
        Singleton()
        {
            cout << "Default constructor called" << endl;
        }
    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        static Singleton* getInstance() 
        {
            lock_guard<mutex> lock(mtx);
            if(!sobj)
            {
                sobj = new Singleton();
            }
            return sobj;
        }
        void display()
        {
            cout << "display function called" << endl;
        }
};
Singleton* Singleton :: sobj = nullptr;
mutex Singleton :: mtx;
void getSingletonInstance()
{
    Singleton* instance = Singleton :: getInstance();
    instance->display();
}
int main()
{
    thread t1(getSingletonInstance);
    thread t2(getSingletonInstance);
    t1.join();
    t2.join();
    return 0;
}


