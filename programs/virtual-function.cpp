#include<iostream>
#include<cmath>
using namespace std;

// Abstract class
class Shape
{
    public:
        virtual void area() = 0; // Pure virtual function
        virtual ~Shape() {} // Virtual destructor 
};

class Circle : public Shape
{
    private:
        double radius;
    public:
        Circle(double r) : radius(r){}
        void area() override
        {
            cout << "Area of Circle: " << M_PI * radius * radius << endl;
        }
};

class Rectangle : public Shape
{
    private:
        double length, width;
    public:
        Rectangle(double l, double w) : length(l), width(w) {}
        void area() override
        {
            cout << "Area of Rectangle: " << length * width << endl;
            
        }
};

class Triangle : public Shape
{
    private:
        double base, height;
    public:
        Triangle(double b, double h) : base(b), height(h) {}
        void area() override
        {
            cout << "Area of Triangle: " << 0.5 * base * height << endl;
        }
};

int main()
{
    Shape* shapes[3];
    shapes[0] = new Circle(10.5);
    shapes[1] = new Rectangle(12.5, 8.5);
    shapes[2] = new Triangle(6.5, 9.5);
    for(int i = 0; i < 3; i++)
    {
        shapes[i]->area();
    }
    for(int i = 0; i < 3; i++)
    {
        delete shapes[i];
    }
    return 0;
}
