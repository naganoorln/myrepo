#include<stdlib.h>
class A 
{
    private:
        //void* operator new(std::size_t size);
    public:
        void* operator new(std::size_t size) = delete;
};

int main()
{
    A *obj = new A();
    return 0;
}