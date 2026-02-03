#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr){}
};
class CircularSinglyLinkedList
{
    private:
        Node* head;
    public:
        CircularSinglyLinkedList() : head(nullptr){}
        ~CircularSinglyLinkedList()
        {
            if(!head)
            {
                return;
            }
            Node* current = head->next;
            while(current && current != head)
            {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            delete head;
            head = nullptr;
        }
        void insertNode(int value)
        {
            Node* newnode = new Node(value);
            if(!head)
            {
                head = newnode;
                head->next = head;
                return;
            }
            Node* current = head;
            while(current->next != head)
            {
                current = current->next;
            }
            current->next = newnode;
            newnode->next = head;
        }
        void deleteNodeByKey(int key)
        {
            if(!head)
            {
                return;
            }
            if(head->data == key)
            {
                if(head->next == head)
                {
                    delete head;
                    head = nullptr;
                    return;
                }
                Node* last = head;
                while(last->next != head)
                {
                    last = last->next;
                }
                Node* temp = head;
                head = head->next;
                last->next = head;
                delete temp;
                return;
            }
            Node* current = head;
            while(current->next != head && current->next->data != key)
            {
                current = current->next;
            }
            if(current->next == head)
            {
                cout << "There is no key matching in the list." << endl;
                return;
            }
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        void displayList()
        {
            if(!head)
            {
                cout << "List is empty!." << endl;
                return;
            }
            Node* current = head;
            do 
            {
                cout << current->data << " ";
                current = current->next;
            }while(current != head);
            cout << endl;
        }
};
int main()
{
    CircularSinglyLinkedList cslist;
    cslist.insertNode(10);
    cslist.insertNode(20);
    cslist.insertNode(30);
    cslist.insertNode(40);
    cslist.insertNode(50);
    cout << "Original list:";
    cslist.displayList();
    cslist.deleteNodeByKey(50);
    cout << "List after deletion:";
    cslist.displayList();
    return 0;
}


 