#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left, *right;
}NODE;

NODE* newnode(int value)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = value;
    temp->left = temp->right = NULL;
    return temp;
}

NODE* insert(NODE* root, int value)
{
    if(root == NULL)
            return newnode(value);
    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

NODE* search(NODE* root, int key)
{
    if(root == NULL || key == root->data)
        return root;
    if(key < root->data)
        return search(root->left, key);
    else if(key > root->data) 
        return search(root->right, key);
}

NODE* minValueNode(NODE* node)
{
    NODE* current = node;
    while(current && current->left != NULL)
        current = current->left;
    return current;    
}
NODE* delete(NODE* root, int key)
{
    if(root == NULL)
        return root;
    if(key < root->data)
        root->left = delete(root->left, key);
    else if(key > root->data)
        root->right = delete(root->right, key);
    else {
        if(root->left == NULL)
        {
            NODE* temp = root->right;
            free(root);
            return temp;
        } else if(root->right == NULL) {
            NODE* temp = root->left;
            free(root);
            return temp;
        }
        NODE* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}
void inorder(NODE* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
int main()
{
    NODE* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    printf("Inorder:");
    inorder(root);
    return 0;
}