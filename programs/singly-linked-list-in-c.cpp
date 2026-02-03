#include <iostream>
using namespace std;
class Node
{
    public:
        int data;
        Node* next;
        Node(int value) : next(nullptr), data(value) {}
};

class LinkedList
{
    private:
    Node* head;
    public:
        LinkedList() : head(nullptr) {}
    void insertNode(int value)
    {
        Node* newnode = new Node(value);
        if(!head)
        {
            head = newnode;
            return;
        }
        Node* temp = head;
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
    void displayList()
    {
        Node* temp = head;
        while(temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
int main()
{
    LinkedList list;
    list.insertNode(10);
    list.insertNode(20);
    list.insertNode(30);
    list.insertNode(40);
    list.insertNode(50);
    list.displayList();
    return 0;
}
