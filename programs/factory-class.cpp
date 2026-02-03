#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <map>
#include <stdexcept>
using namespace std;
class Shape
{
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        ~Shape(){}
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
        Circle(int r) : radius(r) {}
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
        enum class Shapetype
        {
            SQUARE,
            CIRCLE
        };
        static unique_ptr<Shape> createShape(Shapetype type, double value)
        {
            switch(type)
            {
                
                case Shapetype :: SQUARE:
                     return make_unique<Square>(value);
                case Shapetype :: CIRCLE:
                    return make_unique<Circle>(value);
                default:
                    throw
                    invalid_argument("Invalid Shape type!.");
            }
        }
        static string typeToString(Shapetype type)
        {
            switch(type)
            {
                case Shapetype :: SQUARE:
                    return "Square";
                case Shapetype :: CIRCLE:
                    return "Circle";
                default:
                    throw
                    invalid_argument("Invalid type!.");
            }
        }
};
int main()
{
    map<ShapeFactory::Shapetype, unique_ptr<Shape>> shapeMap;
    vector<pair<ShapeFactory :: Shapetype, double>> inputs = {
                                                        {ShapeFactory :: Shapetype :: SQUARE, 5.7},
                                                        {ShapeFactory :: Shapetype :: CIRCLE, 6.0}
                                                        
    };
    /*for(auto& [type, value] : inputs)
    {
        shapeMap[type] = ShapeFactory :: createShape(type, value);
    }
    for(auto& [type, shape] : shapeMap)
    {
        cout << "Area of " << ShapeFactory :: typeToString(type) << ": " << shape->area() << endl;      
        cout << "Perimeter of " << ShapeFactory :: typeToString(type) << ": " << shape->perimeter() << endl;   
    }*/
    for(auto it = inputs.begin(); it != inputs.end(); ++it)
    {
        ShapeFactory :: Shapetype type = it->first;
        double value = it->second;
        shapeMap[type] = ShapeFactory :: createShape(type, value);
    }
    for(auto it = shapeMap.begin(); it != shapeMap.end(); ++it)
    {
        ShapeFactory :: Shapetype type = it->first; 
        //unique_ptr<Shape> shape = move(it->second); // works move ownership 
        Shape* shape = it->second.get(); // raw pointer
        cout << "Area of " << ShapeFactory :: typeToString(type) << ": " << shape->area() << endl;      
        cout << "Perimeter of " << ShapeFactory :: typeToString(type) << ": " << shape->perimeter() << endl;   
    }
    
    return 0;
}
        