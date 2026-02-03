#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr){}
};
class DoublyLinkedList
{
    private:
        Node* head;
    public:
        DoublyLinkedList() : head(nullptr){}
        ~DoublyLinkedList()
        {
            Node* current = head;
            while(current)
            {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        void insertNode(int value)
        {
            Node* newnode = new Node(value);
            if(!head)
            {
                head = newnode;
                return;
            }
            Node* current = head;
            while(current->next)
            {
                current = current->next;
            }
            current->next = newnode;
            newnode->prev = current;
        }
        void deleteNodeByKey(int key)
        {
            if(head && head->data == key)
            {  
                Node* temp = head;
                head = head->next;
                if(head)
                {
                    head->prev = nullptr;
                }
                delete temp;
                return;
            }
            if(!head)
            {
                cout << "List is empty!." << endl;
                return;
            }
            Node* current = head->next;
            while(current && current->data != key)
            {
                current = current->next;
            }
            if(!current)
            {
                cout << "There is no matching key in the list." << endl;
                return;
            }
            current->prev->next = current->next;
            if(current->next)
            {
                current->next->prev = current->prev;
            }
            delete current;
        }
        void displayList()
        {
            Node* current = head;
            while(current)
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
};
int main()
{
    DoublyLinkedList dlist;
    dlist.insertNode(10);
    dlist.insertNode(20);
    dlist.insertNode(30);
    dlist.insertNode(40);
    dlist.insertNode(50);
    cout << "original list:";
    dlist.displayList();
    dlist.deleteNodeByKey(50);
    cout << "List after deletion:";
    dlist.displayList();
    return 0;
}