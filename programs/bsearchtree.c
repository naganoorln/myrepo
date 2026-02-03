/* Binary search tree */
#include <stdio.h>
#include <stdlib.h>

struct Node
{
   int data; 
   struct Node *left, *right;
};
struct Node* createNode(int idata)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = idata;
    newnode->left = newnode->right = NULL;
    return newnode;
}

struct Node* insertNode(struct Node* root, int indata)
{
    if(root == NULL)
    {
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = indata;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
    }
    if(indata < root->data)
    {
        root->left = insertNode(root->left, indata);
    } else if(indata > root->data) {
        root->right = insertNode(root->right, indata);
    }
    return root;
}
struct Node* binarySearch(struct Node* root, int key)
{
    if(root == NULL || root->data == key)
    {
        return root;
    }
    if(key < root->data)
    {
        return binarySearch(root->left, key);
    } else {
        return binarySearch(root->right, key);
    }
}
void inOrder(struct Node* root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
        
    }
}
void preOrder(struct Node* root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void postOrder(struct Node* root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}
int main()
{
    struct Node* root = NULL;
    root = insertNode(root, 30 );
    insertNode(root, 15);
    insertNode(root, 10);
    insertNode(root, 20);
    insertNode(root, 60);
    insertNode(root, 40);
    insertNode(root, 50);
    printf("OUTPUT:\n");
    printf("Inorder: ");
    inOrder(root);
    printf("\n");
    printf("Preorder: ");
    preOrder(root);
    printf("\n");
    printf("Postorder: ");
    postOrder(root);
    int key = 30;
    printf("\n");
    if(binarySearch(root, key))
        printf("%d found in BST.\n", key);
    else
        printf("%d not found in BST.\n", key);
    return 0;
}
