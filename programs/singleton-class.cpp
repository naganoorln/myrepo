/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
// Implimentation of singletone class
#include <iostream>
using namespace std;
class singletone
{
    private:
        static singletone* instance;
        singletone()
        {
            cout << "singletone instance created" << endl;
        }
        ~singletone()
        {
            cout << "singletone instance destroyed" << endl;
        }
    public:
        static singletone& getInstance()
        {
            if(!instance)
            {
                instance = new singletone();
            }
            return *instance;
        }
        // Delete the copy constructor and assignment operator
        singletone(const singletone&) = delete;
        singletone& operator=(const singletone&) = delete;
};
singletone* singletone::instance = nullptr;
int main()
{
    singletone& instance = singletone::getInstance();
}