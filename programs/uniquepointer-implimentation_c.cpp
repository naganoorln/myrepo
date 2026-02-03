#include <iostream>
using namespace std;
template <typename T>
class Unique_Pointer
{
    private:
        T* ptr;
    public:
        explicit Unique_Pointer(T* pointer = nullptr) : ptr(pointer){}
        ~Unique_Pointer()
        {
            delete ptr;
        }
        // Delete copy constructor and assignment operator-object copy is not allowed
        Unique_Pointer(const Unique_Pointer&) = delete;
        Unique_Pointer& operator=(const Unique_Pointer&) = delete;
        // Move copy constructor and Move assignment operator
        Unique_Pointer(Unique_Pointer&& other) noexcept
        {
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        Unique_Pointer& operator=(Unique_Pointer&& other) noexcept
        {
            
            if(this != &other)
            {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }
        // Dereference opeartor overloading
        T& operator*() const 
        {
            return *ptr;
        }
        // -> opeartor overloading
        T* operator->() const
        {
            return ptr;
        }
        // Get raw pointer
        T* get() const
        {
            return ptr;
        }
        void reset(T* pointer = nullptr)
        {
            delete ptr;
            ptr = pointer;
            pointer = nullptr;
        }
        T* release()
        {
            T* temp = ptr;
            ptr = nullptr;
            return temp;
        }
};
class A 
{
    private:
        int a;
    public:
        A(int b) : a(b){}
        void show()
        {
            cout << "Class A :" << a << endl; 
        }
};
int main()
{
    Unique_Pointer<int> uptr(new int(10));
    cout << *uptr << endl;
    cout << *(uptr.get()) << endl;
    Unique_Pointer<int> uptr1 = move(uptr);
    if(!uptr.get())
    {
        cout << "uptr is empty!." << endl;
    }
    cout << *(uptr1) <<  endl;
    cout << *(uptr1.get()) << endl;
    Unique_Pointer<int>uptr2(new int(20));
    cout << *(uptr2) <<  endl;
    uptr1 = move(uptr2);
    if(!uptr2.get())
    {
        cout << "uptr2 is empty!." << endl;
    }
    cout << *(uptr1) << endl;
    Unique_Pointer<int> uptr3(new int(30));
    uptr1.reset(new int(40));
    cout << *uptr1 << endl;
    int* temp = uptr1.release();
    cout << *temp << endl;
    delete temp;
    Unique_Pointer<A> auptr(new A(50));
    auptr->show();
    (*auptr).show();
    (auptr.get())->show();
    (*(auptr.get())).show();
    auptr.reset(new A(100));
    auptr->show();
    return 0;
}