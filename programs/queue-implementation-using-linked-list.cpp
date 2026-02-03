#include <iostream>
using namespace std;
class Node
{
    public:
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
};
class Queue 
{
    private:
        Node* front;
        Node* rear;
    public:
        Queue() : front(nullptr), rear(nullptr) {}
        ~Queue()
        {
            if(!isQueueEmpty())
            {
                dequeue();
            }
        }
        Node* createNode(int value)
        {
            return new Node(value);
        }
        bool isQueueEmpty()
        {
            return front == nullptr;
        }
        void enqueue(int value)
        {
            Node* newnode = createNode(value);
            if(rear == nullptr)
            {
                front = rear = newnode;
                return;
            }
            rear->next = newnode;
            rear = newnode;
        }
        void dequeue()
        {
            if(isQueueEmpty())
            {
                cout << "Queue is empty!." << endl;
                return;
            }
            Node* temp = front;
            front = front->next;
            if(front == nullptr)
            {
                rear = nullptr;
            }
            cout << "Dequeued element is:" << temp->data << endl;
            delete temp;
        }
        int peek()
        {
            if(isQueueEmpty())
            {
                cout << "Queue is empty!." << endl;
                return -1;
            }
            return front->data;
        }
        void displayQueue()
        {
            if(isQueueEmpty())
            {
                cout << "Queue is empty!." << endl;
                return;
            }
            Node* temp = front;
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
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    cout << "Queue is:";
    q.displayQueue();
    cout << "Peek in queue is:" << q.peek() << endl;
    q.dequeue();
    cout << "Queue after dequeue is:";
    q.displayQueue();
    return 0;
}