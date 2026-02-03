 // Unique pointer-Smart pointer
 #include <iostream>
 class Mass
 {
     private:
        double value;
     public:
        Mass(double v) : value(v)
        {
            std::cout << "Mass object created: " << value << std::endl;
        }
        ~Mass()
        {
            std::cout << "Mass object destroyed: " << value << std::endl;
        }
        void show() const
        {
            std::cout << "Mass: " << value << std::endl;
        }
 };
 template <typename T>
 class UniquePointer
 {
     private:
        T* ptr;
     public:
        explicit UniquePointer(T* p = nullptr) : ptr(p){}
        ~UniquePointer(){ delete ptr;}
        //Delete copy constructor and assignment opeartor- avoid shallow copy
        UniquePointer(const UniquePointer&) = delete;
        UniquePointer& operator=(const UniquePointer&) = delete;
        // Move copy constructor-Transfer owenership
        UniquePointer(UniquePointer&& other) noexcept
        {
            std::cout << "Move copy constructor called." << std::endl;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        //Move assignment operator-Transfer ownership
        UniquePointer& operator=(UniquePointer&& other) noexcept
        {
            std::cout << "Move assignment opeartor called." << std::endl;
            if(this != &other)
            {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }
        // Deference operator overloading
        T& operator*() const
        {
            std::cout << "Dereference opeartor(*) called." << std::endl;
            return *ptr;
        }
        // ->opeartor overloading
        T* operator->() const
        {
            std::cout << "->opeartor called." << std::endl;
            return ptr;
        }
        // Get raw pointer
        T* get() const
        {
            return ptr;
        }
        //Release ownership-caller must call delete manually
        T* release()
        {
            std::cout << "release ownership called." << std::endl;
            T*temp = ptr;
            ptr = nullptr;
            return temp;
        }
        // Reset pointer
        void reset(T* p = nullptr)
        {
            delete ptr;
            ptr = p;
        }
};
int main()
{
   UniquePointer<Mass> uptr(new Mass(70.5));
   uptr->show(); 
   (*uptr).show();
   UniquePointer<Mass> uptr1 = std::move(uptr);
   if(!uptr.get())
   {
       std::cout << "uptr is empty." << std::endl;
   }
   uptr1->show();
   (*uptr1).show();
   UniquePointer<Mass> uptr2(new Mass(85.7));
   UniquePointer<Mass> uptr3(new Mass(90.5));
   uptr2->show();
   (*uptr2).show();
   uptr3->show();
   (*uptr3).show();
   uptr2 = std::move(uptr3);
   if(!uptr3.get())
   {
       std::cout << "uptr3 is empty." << std::endl;
   }
   (*uptr2).show();
   uptr2->show();
   Mass* mptr = uptr2.release();
   mptr->show();
   if(!uptr2.get())
   {
       std::cout << "uptr2 is empty." << std::endl;
   }
   UniquePointer<Mass> uptr4(new Mass(110.7));
   (*uptr4).show();
   uptr4.reset(new Mass(120.7));
   (*uptr4).show();
   delete mptr;
   return 0;
 }


 
 
 

        
        
        
        