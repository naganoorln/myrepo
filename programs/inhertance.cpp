#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class Shape
{
    protected:
        static int idCounter; // Auto-incremented idCounter
        int id;
    public:
        Shape(); // Constructor to assigne unique ID 
        virtual double area() = 0; // Pure virtual function for area
        virtual string getType() = 0; // Returns the shape typede
        virtual void display() = 0; // Display shape details
        virtual void saveToFile(ofstream& file) = 0; // Save to file
        virtual ~Shape(); // virtual destructor
};

class Rectangle : public Shape
{
    private:
        double length, breadth;
    public:
        Rectangle(double l, double b);
        double area() override;
        string getType() override;
        void display() override;
        void saveToFile(ofstream& file) override;
};

class Circle : public Shape
{
    private:
        double radius;
    public:
        Circle(double r);
        double area() override;
        string getType() override;
        void display() override;
        void saveToFile(ofstream& file) override;
};

class Triangle: public Shape
{
    private:
        double base, height;
    public:
        Triangle(double base, double height);
        double area() override;
        string getType() override;
        void display() override;
        void saveToFile(ofstream& file) override;
};

class ShapeFactory
{
    public:
        static Shape* createShape(string type, int a, int b, int c);
};
class ShapeManager
{
    private:
        vector<Shape*>shapes;
        string filename;
    public:
        ShapeManager(string fname);
        void addShape(Shape* shape);
        void displayShapes();
        double totalArea();
        void saveShapesToFile();
        void displayShapesFromFile();
        ~ShapeManager();
};

int Shape::idCounter = 0;
Shape::Shape()
{
    id = ++idCounter;
}
Shape::~Shape() {}

Rectangle::Rectangle(double l, double b) : length(l), breadth(b) {}
double Rectangle::area()
{
    return length*breadth;
}
string Rectangle::getType()
{
    return "Rectangle";
}
void Rectangle::display()
{
    cout << "Rectangle [ID: " << id << "] Length: " << length << ", Breadth: " << breadth << ", Area: "
    << area() << endl;
}
void Rectangle::saveToFile(ofstream& file)
{
    file << "Rectangle " << length << " " <<
    breadth << " " << area() << endl;
}

Circle::Circle(double r) : radius(r) {}
double Circle::area()
{
    return 3.14159 * radius * radius;
}
string Circle::getType()
{
    return "Circle";
}
void Circle::display()
{
    cout << "Circle [ID: " << id << "] Radius: " 
    << radius << ", Area: " << area() << endl;
}
void Circle::saveToFile(ofstream& file)
{
    file << "Circle " << radius << " " << area() << endl;
}

Triangle::Triangle(double b, double h) : base(b), height(h) {}
double Triangle::area()
{
    return 0.5 * base * height;    
}
string Triangle::getType()
{
    return "Triangle";
}
void Triangle::display()
{
    cout << "Triangle [ID: " << id << "] Base: " << base << ", Height: "
    << height << ", Area: " << area() << endl;
}
void Triangle::saveToFile(ofstream& file)
{
    file << "Triangle " << base << " " << height << " " << area() << endl;
}

Shape* ShapeFactory::createShape(string type, int a, int b, int c = 0)
{
    if(type == "Rectangle")
    {
        return new Rectangle(a, b);
    } else if(type == "Circle") {
        return new Circle(c);
    } else if(type == "Triangle") {
        return new Triangle(a, b);
    } else {
        return nullptr;
    }
}

ShapeManager::ShapeManager(string fname) : filename(fname) {} 
void ShapeManager::addShape(Shape* shape)
{
    shapes.push_back(shape);
    cout << shape->getType() << " added successfully" << endl;
}
void ShapeManager::displayShapes()
{
    if(shapes.empty())
    {
        cout << "No shapes available." << endl;
        return;
    }
    cout << "Displaying all shapes." << endl;
    for(auto shape : shapes)
    {
        shape->display();
    }
}
void ShapeManager::saveShapesToFile()
{
    ofstream file(filename);
    if(!file)
    {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }
    for(auto shape : shapes)
    {
        shape->saveToFile(file);
    }
    file.close();
    cout << "Shapes saved to file." << endl;
}
void ShapeManager::displayShapesFromFile()
{
    ifstream file(filename);
    if(!file)
    {
        cout << "Error: unable to open file " << filename << endl;
        return;
    }
    string line;
    cout << endl << "File Content(" << filename << "):" << endl;
    while(getline(file, line))
    {
        cout << line << endl;
    }
    file.close();
}
ShapeManager::~ShapeManager()
{
    for(auto shape : shapes)
    {
        delete shape;
    }
}

int main()
{
    ShapeManager manager("shapes.txt");
    int choice;

    do {
        cout << "\n==== Shape Manager Menu ====\n"
             << "1. Add Rectangle\n"
             << "2. Add Circle\n"
             << "3. Add Triangle\n"
             << "4. Display All Shapes\n"
             << "5. Save Shapes to File\n"
             << "6. Display Shapes from File\n"
             << "7. Exit\n"
             << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double l, b;
                cout << "Enter length and breadth: ";
                cin >> l >> b;
                manager.addShape(ShapeFactory::createShape("Rectangle", l, b));
                break;
            }
            case 2: {
                double r;
                cout << "Enter radius: ";
                cin >> r;
                manager.addShape(ShapeFactory::createShape("Circle", 0, 0, r));
                break;
            }
            case 3: {
                double b, h;
                cout << "Enter base and height: ";
                cin >> b >> h;
                manager.addShape(ShapeFactory::createShape("Triangle", b, h));
                break;
            }
            case 4: manager.displayShapes(); break;
            case 5: manager.saveShapesToFile(); break;
            case 6: manager.displayShapesFromFile(); break;
            case 7: cout << "Exiting program.\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}




    

    

  