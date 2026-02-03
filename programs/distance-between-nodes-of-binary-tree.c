#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* LCA(struct Node* root, int n1, int n2)
{
    if(root == NULL)
        return NULL;
    if(root->data == n1 || root->data == n2)
        return root;
    struct Node* left = LCA(root->left, n1, n2);
    struct Node* right = LCA(root->right, n1, n2);
    if(left != NULL && right!= NULL)
        return root;
    if(left == NULL && right == NULL)
        return NULL;
    return left != NULL ? LCA(root->left, n1, n2) : LCA(root->right, n1, n2);
}
int findLevel(struct Node* root, int key, int level)
{
    if(root == NULL)
        return -1;
    if(root->data == key)
        return level;
    int left = findLevel(root->left, key, level + 1);
    if( left == -1)
        return findLevel(root->right, key, level + 1);
    return left;
}
int findDistance(struct Node* root, int a, int b)
{
    struct Node* lca = LCA(root, a, b);
    int d1 = findLevel(lca, a, 0);
    int d2 = findLevel(lca, b, 0);
    return d1 + d2;
}
struct Node* createNode(int value)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
int main()
{
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
  
    printf("%d\n", findDistance(root, 4, 7));

    return 0;
}