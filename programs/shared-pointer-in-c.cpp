// Implimentation of shared pointer 
#include <iostream>
template <typename T>
class SharedPointer
{
    private:
        T* ptr;
        int* refcount;
    public:
        SharedPointer(T* p = nullptr) : ptr(p), refcount(new int(1))
        {
            std::cout << "Constructor called" << std::endl;
            if(!p) (*refcount) = 0;
            
        }
        // Copy constructor
        SharedPointer(const SharedPointer& other)
        {
            std::cout << "Copy constructor called" << std::endl;
            ptr = other.ptr;
            refcount = other.refcount;
            if(ptr) (*refcount)++;
        }
        // Assignment operator
        SharedPointer& operator=(const SharedPointer& other)
        {
            std::cout << "Assignment operator called" << std::endl;
            if(this != &other)
            {
                release();
                ptr = other.ptr;
                refcount = other.refcount;
                if(ptr) (*refcount)++;
            }
            return *this;
        }
        // Move copy constructor
        SharedPointer(SharedPointer&& other)
        {
            std::cout << "Move copy constructor called" << std::endl;
            ptr = other.ptr;
            refcount = other.refcount;
            other.ptr = nullptr;
            other.refcount = nullptr;
        }
        // Move assignment operator
        SharedPointer& operator=(SharedPointer&& other)
        {
            std::cout << "Move assignment opeartor called" << std::endl;
            if(this != &other)
            {
                release();
                ptr = other.ptr;
                refcount = other.refcount;
                other.ptr = nullptr;
                other.refcount = nullptr;
            }
            return *this;
        }
        ~SharedPointer()
        { 
            std::cout << "Destructor called" << std::endl;
            release();
            
        }
       // Dereference * operator overloading
       T& operator*() const
       {
           return *ptr;
       }
       // -> operator overloading
       T* operator->() const
       {
           return ptr;
       }
       // Get raw pointer
       T* get() const
       {
           return ptr;
       }
       // use count(refcount)
       int use_count() const
       {
           return ptr ? (*refcount) : 0;
       }
       // unique user ?
       bool unique() const
       {
           return (*refcount) == 1;
       }
    private:
        void release()
        {
            if(ptr && --(*refcount) == 0)
            {
                delete ptr;
                delete refcount;
            }
            ptr = nullptr;
            refcount = nullptr;
        }
};
int main()
{
    SharedPointer<int> sp1(new int(5));
    std::cout << "sp1.refcount: " << sp1.use_count() << std::endl;
    SharedPointer<int> sp2 = sp1;
    std::cout << "sp1.refcount: " << sp1.use_count() << std::endl;
    std::cout << "sp2.refcount: " << sp2.use_count() << std::endl;
    SharedPointer<int> sp3(new int(11));
    SharedPointer<int> sp4 = std::move(sp3);
    if(!sp3.get())
    {
        std::cout << "sp3 is not existing. It is moved  to sp4" << std::endl;
    }
    
    std::cout << "sp3.refcount: " << sp3.use_count() << std::endl;
    std::cout << "sp4.refcount: " << sp4.use_count() << std::endl;
    SharedPointer<int> sp5(new int(7));
    SharedPointer<int> sp6(new int(9));
    std::cout << "sp5.refcount: " << sp5.use_count() << std::endl;
    std::cout << "sp6.refcount: " << sp6.use_count() << std::endl;
    sp5 = sp6;
    std::cout << "sp5.refcount: " << sp5.use_count() << std::endl;
    std::cout << "sp6.refcount: " << sp6.use_count() << std::endl;
    SharedPointer<int> sp7(new int(11));
    SharedPointer<int> sp8(new int(15));
    sp8 = std::move(sp7);
    if(!sp7.get())
    {
        std::cout << "sp7 is not existing. It is moved  to sp8" << std::endl;
    }
    
    std::cout << "sp7.refcount: " << sp7.use_count() << std::endl;
    std::cout << "sp8.refcount: " << sp8.use_count() << std::endl;
    return 0;
}
