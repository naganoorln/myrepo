#include <iostream>
class Vector 
{
    private:
        int* arr;
        int size;
        int capacity;
        void resize()
        {
            capacity *= 2;
            int* temp = new int[capacity];
            for(int i = 0; i < size; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
        public:
            Vector(int cap = 2) : size(0), capacity(cap)
            {
                arr = new int[capacity];
            }
            ~Vector()
            {
                delete[] arr;
            }
            void push_back(int value)
            {
                if(size == capacity)
                {
                    resize();
                }
                arr[size++] = value;
            }
            void pop_back()
            {
                if(size > 0)
                {
                    size--;
                }
            }
            const int& operator[](int index) const
            {
                if(index < 0 && index >= size)
                {
                    throw
                    std:: out_of_range("Index out of bounds");
                }
                return arr[index];
            }
            int getSize()
            {
                return size;
                
            }
            int getCapacity()
            {
                return capacity;
            }
            bool isEmpty() const 
            {
                return size == 0;
            }
            void insert(int index, int value)
            {
                if(index < 0 || index > size)
                {
                    throw
                    std::out_of_range("index out of bounds");
                }
                if(size == capacity)
                {
                    resize();
                }
                for(int i = size; i > index; i--)
                {
                    arr[i] = arr[i -1];
                }
                arr[index] = value;
                size++;
            }
            void erase(int index)
            {
                if(index < 0 || index > size)
                {
                    throw
                    std::out_of_range("Index out of bounds");
                }
                for(int i = index; i < size -1; i++)
                {
                    arr[i] = arr[i+1];
                }
                size--;
            }
            void claer()
            {
                size = 0;
            }
            void shrinkToFit()
            {
                if(capacity > size)
                {
                    int*temp = new int[size];
                    for(int i = 0; i < size; i++)
                    {
                        temp[i] = arr[i];
                    }
                    delete[] arr;
                    arr = temp;
                    capacity = size;
                }
            }
            void print() const
            {
                for(int i = 0; i < size; i++)
                {
                   std::cout << arr[i] << " ";
                }
                std::cout << std::endl;
            }
    
};
int main()
{
    Vector vec;
    vec.push_back(10);
    vec.push_back(15);
    vec.push_back(20);
    vec.push_back(25);
    vec.push_back(30);
    std::cout << "Vector Size: " << vec.getSize() << std::endl;
    std::cout << "Vector Capacity: " << vec.getCapacity() << std::endl;
    vec.print();
    vec.pop_back();
    vec.print();
    vec.insert(4, 35);
    vec.print();
    vec.erase(3);
    vec.print();
    std::cout << vec[3] << std::endl;
    return 0;
}
            