#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
class Singleton
{
private:
	static Singleton* instance;
	static mutex mtx;
	//Define default constructor in private
	Singleton()
	{
		cout << "Default constructor called." << endl;
	}
public:
	// Delete copy constructor
	Singleton(const Singleton&) = delete;
	// Delete assignment operator
	Singleton& operator=(const Singleton&) = delete;
	static Singleton* getInstance()
	{
		lock_guard<mutex> lock(mtx);
		if(!instance)
		{
			instance = new Singleton();
		}
		return instance;
	}
	void showMessage()
	{
		cout << "Singleton object." << endl;
	}
};
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;
void getSingletonInstance()
{
	Singleton* instance = Singleton::getInstance();
	instance->showMessage();
}
int main()
{
	thread t1(getSingletonInstance);
	thread t2(getSingletonInstance);
	t1.join();
	t2.join();
	return 0;
}

