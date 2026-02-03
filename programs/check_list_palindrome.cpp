#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr){}
};
class NodeList
{
    private:
        Node* head;
    public:
        NodeList() : head(nullptr){}
        void append(int value)
        {
            Node* newnode = new Node(value);
            if(!head)
            {
                head = newnode; 
            } else {
                Node* current = head;
                while(current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = newnode;
            }
        }
        bool isListPalindrome()
        {
            Node* slow = head;
            Node* fast = head;
            while(fast && fast->next)
            {
                slow = slow->next;
                fast = fast->next->next;
            }
            Node* rev = nullptr;
            while(slow != nullptr)
            {
                Node* next = slow->next;
                slow->next = rev;
                rev = slow;
                slow = next;
            }
            Node* left = head;
            Node* right = rev;
            while(right != nullptr)
            {
                if(right->data != left->data)
                {
                    return false;
                }
                left = left->next;
                right = right->next;
            }
            return true;
        }
};
int main()
{
    NodeList list1,list2;
    list1.append(10);
    list1.append(12);
    list1.append(13);
    list1.append(12);
    list1.append(10);
    
    list2.append(10);
    list2.append(12);
    list2.append(13);
    list2.append(14);
    list2.append(12);
    list2.append(10);
    if(list1.isListPalindrome())
    {
        cout << "list1 is palindrome" << endl;
    } else {
        cout << "list1 is not palindrome" <<endl;
    }
    if(list2.isListPalindrome())
    {
        cout << "list2 is palindrome" << endl;
    } else {
        cout << "list2 is not palindrome" <<endl;
    }
    return 0;
}