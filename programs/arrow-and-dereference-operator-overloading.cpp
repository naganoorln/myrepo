#include <iostream>
using namespace std;
#include <memory>

class MyClass
{
    private:
        int data;
    public:
        MyClass() : data(0)
        {
            cout << "Default constructor called." << endl;
        }
        MyClass(int value) : data(value)
        {
            cout << "Parameterized constructur is called with value " << value << endl;
        }
        MyClass(const MyClass& other) : data(other.data)
        {
            cout << "Copy constructor called" << endl;
        }
        MyClass& operator=(const MyClass& other)
        {
            if(this != &other)
            {
                data = other.data;
                cout << "Assignment operator is called." << endl;
            }
            return *this;
        }
        MyClass* operator->()
        {
            cout << "Arrow('->') operator is called." << endl;
            return this;
        }
        int operator*() const 
        {
            cout << "Dereference('*') operator is called." << endl;
            return data;
        }
        void display() const
        {
            cout << "Data: " << data << endl;
        }
};
int main()
{
    unique_ptr<MyClass> obj1 = make_unique<MyClass>();
    unique_ptr<MyClass> obj2 = make_unique<MyClass>(42);
    MyClass obj3(*obj2);
    obj3 = *obj1;
    (*obj2)->display();
    cout << "Dereferenced data: " << *(*obj2) << endl;
    return 0;
}