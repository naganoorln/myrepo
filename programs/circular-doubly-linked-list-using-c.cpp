#include <iostream> 
using namespace std;
struct Node
{
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr){}
};
class CircularDoublyLinkedList
{
    private:
        Node* head;
    public:
        CircularDoublyLinkedList() : head(nullptr){}
        ~CircularDoublyLinkedList()
        {
            
            if(!head)
            {
                return;
            }
            Node* current = head->next;
            while(current != head)
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
                newnode->next = newnode->prev = newnode;
                head = newnode;
                return;
            }
            Node* last = head->prev;
            last->next = newnode;
            newnode->prev = last;
            newnode->next = head;
            head->prev = newnode;
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
                Node* last = head->prev;
                Node* temp = head;
                head = head->next;
                last->next = head;
                head->prev = last;
                delete temp;
                return;
            }
            Node* current = head->next;
            while(current != head && current->data != key)
            {
                current = current->next;
            }
            if(current == head)
            {
                cout << "There is no key matching in the list." << endl;
                return;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        void displayList()
        {
            if(!head)
            {
                cout << "List is empty!." << endl;
            }
            Node* current = head;
            do 
            {
                cout << current->data << " ";
                current = current->next;
            } while(current != head);
            cout << endl;
        }
};
int main()
{
    CircularDoublyLinkedList cdlist;
    cdlist.insertNode(10);
    cdlist.insertNode(20);
    cdlist.insertNode(30);
    cdlist.insertNode(40);
    cdlist.insertNode(50);
    cout << "Original list:";
    cdlist.displayList();
    cdlist.deleteNodeByKey(50);
    cout << "List after deletion:";
    cdlist.displayList();
    return 0;
}