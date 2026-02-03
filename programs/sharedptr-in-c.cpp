// Implimentation of shared pointer */
#include <iostream>
template <typename T>
class SharedPtr
{
    private:
        T* ptr;
        int* refCount;
    punlic:
        // Constructor
        explicit SharedPtr(T* p = nullptr) : ptr(p), refCount(new int(1))
        {
            if(!p) *refCount = 0;
        }
        // Copy constructor.refCount is incresed 
        SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) 
        {
            if(ptr) (*refCount)++
        }
    
        
}