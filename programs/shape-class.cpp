#include <iostream>
#include <cmath>
#include <memory>
#include <stdexcept>
using namespace std;
class Shape
{
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        ~Shape() {}
};
class Square : public Shape
{
    private:
        double side;
    public:
        Square(double s) : side(s) {}
        double area() const override
        {
            return side * side;
        }
        double perimeter() const override
        {
            return 4 * side;
        }
};
class Circle : public Shape
{
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {}
        double area() const override
        {
            return M_PI * radius * radius;
        }
        double perimeter() const override
        {
            return 2 * M_PI * radius;
        }
};

class ShapeFactory
{
    public:
        enum Shapetype
        {
            SQUARE,
            CIRCLE
        };
        static unique_ptr<Shape> createShape(Shapetype type, double value = 0)
        {
            switch(type)
            {
                case SQUARE:
                    return make_unique<Square>(value);
                case CIRCLE:
                    return make_unique<Circle>(value);
                default:
                    throw
                    invalid_argument("Invalid shape type!.");
            }
        }
};
int main()
{
    try
    {
        int input;
        while(1)
        {
            cout << "Enter Shape Type." << endl;
            cout << "0 for Square." << endl;  
            cout << "1 for Circle." << endl;
            cout << "9 for Exit." << endl;
            cin >> input;
            if(input == 9)
            {
                exit(1);
            }
            ShapeFactory::Shapetype type = static_cast<ShapeFactory::Shapetype> (input);
            unique_ptr<Shape> shape;
            if(type == ShapeFactory :: SQUARE )
            {
           
                double side;
                cout << "Enter Side of Square:";
                cin >> side;
                shape = ShapeFactory::createShape(type, side);
                cout << "Area of Square:" << shape->area() << endl;
                cout << "Perimeter of Square:" << shape->perimeter() << endl;
            } else if(type == ShapeFactory :: CIRCLE ) {
                double radius;
                cout << "Enter Radius of Circle:";
                cin >> radius;
                shape = ShapeFactory::createShape(type, radius);
                cout << "Area of Circle:" << shape->area() << endl;
                cout << "Perimeter of Circle:" << shape->perimeter() << endl; 
            } else {
                shape = ShapeFactory::createShape(type);
            }
        }
    }
    catch(invalid_argument& e)
    {
        cerr << "Caught Invalid argument: " << e.what() << endl;
    }
    return 0;
    
}