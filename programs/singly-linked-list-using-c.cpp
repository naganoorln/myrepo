#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr){}
};
class SinglyLinkedList
{
    private:
        Node* head;
    public:
        SinglyLinkedList() : head(nullptr){}
        ~SinglyLinkedList()
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
        }
        void deleteNodeByKey(int key)
        {
            if(head && head->data == key)
            {
               Node* temp = head;
               head = head->next;
               delete temp;
               return;
            }
            if(!head)
            {
                cout << "List is empty!." << endl;
                return;
            }
            Node* current = head->next;
            Node* prev = head;
            while(current && current->data != key)
            {
                prev = current;
                current = current->next;
            }
            if(current == NULL)
            {
                cout <<"There is no key element matching in the list." << endl;
                return;
            }
            prev->next = current->next;
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
    SinglyLinkedList list;
    list.insertNode(10);
    list.insertNode(20);
    list.insertNode(30);
    list.insertNode(40);
    list.insertNode(50);
    cout << "Original list:";
    list.displayList();
    list.deleteNodeByKey(50);
    list.insertNode(60);
    cout << "List after deletion:";
    list.displayList();
    return 0;
}