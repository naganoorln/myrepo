/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

class Node
{
    public:
        int data;
        Node* next;
        Node* prev;
        Node(int data):data(data),
        next(nullptr),prev(nullptr){}
};

class DoublyLinkedList
{
    private:
        Node* head;
        Node* tail;
    public:
        DoublyLinkedList():
        head(nullptr),tail(nullptr){}
        void append(int);
        void deleteMiddleNode();
        void printList();
};
void DoublyLinkedList::append(int value)
{
    Node* newNode = new Node(value);
    if(!head)
    {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}
void DoublyLinkedList::deleteMiddleNode()
{
    Node* slow = head, *fast = head;
    // Find the midddle Node
    while(fast && fast->next)
    {
        fast = fast->next->next;
        if(fast)
        {
            slow = slow->next;
        }
    }
    // delete the middle Node
    if(slow->prev)
    {
        slow->prev->next = slow->next;
    }
    if(slow->next)
    {
        slow->next->prev = slow->prev;
    }
    if(slow == head)
    {
        head = slow->next;
    }
    if(slow == tail)
    {
        tail = slow->prev;
    }
    delete slow;
}
void DoublyLinkedList::printList()
{
    Node* current = head;
    while(current)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
int main()
{
    DoublyLinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);
    cout << "Original List: ";
    list.printList();
    list.deleteMiddleNode();
    cout << "Modified List: ";
    list.printList();
    return 0;
}

    

