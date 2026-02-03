//Stack implimentation using c++ with Menue of stack operations PUSH,POP,DISPLAY and EXIT
#include <iostream>
#define STACK_SIZE 5
using namespace std;

class STACK
{
    private:
        int num[STACK_SIZE];
        int top;
    public:
        STACK();
        int push(int);
        int pop();
        int isEmpty();
        int isFull();
        void displayStack();
};

STACK::STACK()
{
    top = -1;
}

int STACK::isEmpty()
{
    if(top == -1)
    {
        return 1;
    } else {
        return 0;
    }
}

int STACK::isFull()
{
    if(top == (STACK_SIZE - 1))
    {
        return 1;
    } else {
        return 0;
    }
}

int STACK::push(int n)
{
    if(isFull())
    {
        return 0;
    }
    ++top;
    num[top] = n;
    return n;
}

int STACK::pop()
{
    if(isEmpty())
    {
        return 0;
    }  
    int temp = num[top];
    --top;
    return temp;
}

void STACK::displayStack()
{
    cout << "STACK is: ";
    for(int i = top; i >= 0; i--)
        cout << num[i] << " ";
}

int main()
{
    STACK stk;
    int choice,n, temp;
    do
    {
        cout << endl;
        cout << "0 - Exit." << endl;
        cout << "1 - Push number into stack." << endl;
        cout << "2 - Pop number from Stack." << endl;
        cout << "3 - Display stack." << endl;
        
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice)
        {
            case 0:
                break;
            
            case 1:
                cout << "Enter number to insert: ";
                cin >> n;
                temp = stk.push(n);
                if(temp == 0)
                {
                    cout << "STACK is full." << endl;
                } else {
                    cout << temp << " inserted" << endl;
                }
                break;
                
            case 2:
                temp = stk.pop();
                if(temp == 0)
                {
                    cout << "STACK is empty." << endl;
                } else {
                    cout << temp << "is popped." << endl;
                }
                break;
                
            case 3:
                stk.displayStack();
                break;
                
            default:
                cout << "An invalid choice." << endl;
        }
    } while(choice != 0);
        
    return 0;
}
