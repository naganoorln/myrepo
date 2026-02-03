// Implimentation of Binary Tree
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root, int value)
{
    if(root == NULL)
    {
        return createNode(value);
    }
    if(value < root->data)
    {
        root->left = insertNode(root->left, value);
    } else if(value > root->data) {
        root->right = insertNode(root->right, value);
    }
    return root;
}

void inOrderTraversel(struct Node* root)
{
    if(root != NULL)
    {
        inOrderTraversel(root->left);
        printf("%d ",root->data);
        inOrderTraversel(root->right);
    }
}

void preOrderTraversel(struct Node* root)
{
    if(root != NULL)
    {
        printf("%d ",root->data);
        preOrderTraversel(root->left);
        preOrderTraversel(root->right);
    }
}

void postOrderTraversel(struct Node* root)
{
    if(root != NULL)
    {
        postOrderTraversel(root->left);
        postOrderTraversel(root->right);
        printf("%d ",root->data);
    }
}

void freeRoot(struct Node* root)
{
    if(root != NULL)
    {
        freeRoot(root->left);
        freeRoot(root->right);
        free(root);
    }
}

int main()
{
    struct Node* root = NULL;
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);
    
    printf("Inorder Traversal: ");
    inOrderTraversel(root);
    printf("\nPreorder Traversel: ");
    preOrderTraversel(root);
    printf("\nPostorder Traversel: ");
    postOrderTraversel(root);
    freeRoot(root);
    return 0;
}