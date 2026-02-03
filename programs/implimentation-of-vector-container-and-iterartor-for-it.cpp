#include <iostream>

using namespace std;
template <typename T>
class Vector 
{
    private:
        T* data;
        size_t size;
        size_t capacity;
        void resize()
        {
            capacity *= 2;
            T* newData = new T[capacity];
            for(size_t i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete data;
            data = newData;
        }
    public:
        Vector() : size(0), capacity(2)
        {
            data = new T[capacity];
        }
        ~Vector()
        {
            delete[] data;
        }
        void push_back(const T& value)
        {
            if(size == capacity)
            {
                resize();
            }
            data[size++] = value;
        }
        T& operator[](size_t index)
        {
            return data[index];
        }
        size_t getSize()
        {
            return size;
        }
        size_t getCapacity()
        {
            return capacity;
        }
        
        class Iterator
        {
            private:
                T* ptr;
            public:
                Iterator() : ptr(nullptr) {}
                Iterator(T* p) : ptr(p) {}
                T& operator*()
                {
                    return *ptr;
                }
                Iterator& operator++()
                {
                    ++ptr;
                    return *this;
                }
                Iterator operator++(int)
                {
                    Iterator temp = *this;
                    ++ptr;
                    return temp;
                }
                bool operator==(const Iterator& other) const
                {
                    return ptr == other.ptr;
                }
                bool operator!=(const Iterator& other) const
                {
                    return ptr != other.ptr;
                }
        };
        Iterator begin()
        {
            return Iterator(data);
        }
        Iterator end()
        {
            return Iterator(data + size);
        }
};
int main()
{
    Vector<int>vec;
    Vector<int>::Iterator it;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);
    for(it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}