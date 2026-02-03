#include <iostream>
using namespace std;
struct Binarytree
{
    int data;
    Binarytree* left;
    Binarytree* right;
    Binarytree(int value) : data(value), left(nullptr), right(nullptr) {}
};
class Btree 
{
    private:
        Binarytree* root;
    public:
        Btree() : root(nullptr) {}
        void insertNode(int value)
        {
            if(!root)
            {
                root = new Binarytree(value);
                return;
            }
            Binarytree* current = root;
            Binarytree* parent = nullptr;
            while(current != nullptr)
            {
                parent = current;
                if(value < current->data)
                {
                    current = current->left;   
                } else {
                    current = current->right;
                }
            }
            if(value < parent->data)
            {
                parent->left = new Binarytree(value);
            } else {
                parent->right = new Binarytree(value);
            }
        }
};   