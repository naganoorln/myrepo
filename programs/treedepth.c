/* Find the depth of binary tree */
#include <stdio.h>
#include <stdlib.h>
/* Define tree node */
struct Node 
{
    int data;
    struct Node* left;
    struct Node* right;
};
/* Create node */
struct Node* createNode(int value)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
/* Insert node into tree */
struct Node* insertNode(struct Node* root, int value)
{
    if(root == NULL)
    {
        return createNode(value);
    }
    if(value < root->data)
    {
        root->left = insertNode(root->left, value);
    } else {
        root->right = insertNode(root->right, value);
    }
    return root;
}
/* Find the depth of tree */
int depthOfTree(struct Node* root)
{
    if(root == NULL)
    {
        return 0;
    }
    int leftdepth = depthOfTree(root->left);
    int rightdepth = depthOfTree(root->right);
    return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
}
int main()
{
    struct Node* root = NULL;
    root = insertNode(root, 20);
    insertNode(root, 30);
    insertNode(root, 40);
    insertNode(root, 50);
    insertNode(root, 60);
    insertNode(root, 70);
    insertNode(root, 80);
    printf("Depth of tree is %d\n", depthOfTree(root));
    return 0;
}