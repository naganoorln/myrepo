#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Product
{
    public:
        int id;
        string name;
        double price;
        Product(int pid, string pname, double pprice) : id(pid), name(pname), price(pprice) {}
        void display()
        {
            cout <<"Product ID: " << id << ", Name: " << name << ", Price: " << price << endl;
        }
};
class Customer
{
    public:
        int id;
        string name;
        string emailid;
        Customer(int cid, string cname, string cemailid) : id(cid), name(cname), emailid(cemailid) {}
        void display()
        {
            cout << "Customer ID: " << id << ", Name: " << name << ", Emaild ID: " << emailid << endl; 
        }
};
class Order
{
    public;
        int id;
        Customer customer;
        vector<Product> products;
        Order o(int oid. Customer c) : id(oid),customer(c) {}
        void display()
        {
            cout << 
        }
}