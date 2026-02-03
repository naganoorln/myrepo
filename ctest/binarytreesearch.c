/* BST Tree */
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *left, *right;
};
struct Node* createNode(int value)
{
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = value;
        newnode->left = newnode->right = NULL;
	return newnode;
}

struct Node* insertNode(struct Node* root, int value)
{
	if(root == NULL)
		return createNode(value);
	if(value < root->data)
		root->left = insertNode(root->left, value);
	 else if(value > root->data)
		root->right = insertNode(root->right, value);
        return root;
}

struct Node* searchNode(struct Node* root, int key)
{
	if(root == NULL || key == root->data)
		return root;
	if(key < root->data)
		return searchNode(root->left, key);
	else if(key > root->data)
		return searchNode(root->right, key);
}
struct Node* minValueNode(struct Node* node)
{
	struct Node* current = node;
	while(current && current->left != NULL)
		current = current->left;
	return current;
}

struct Node* deleteNode(struct Node* root, int key)
{
	if(root == NULL)
		return root;
	if(key < root->data)
		root->left = deleteNode(root->left, key);
	else if(key > root->data)
		root->right = deleteNode(root->right, key);
	else {
		if(root->left == NULL)
		{
			struct Node* temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL) {
			struct Node* temp = root->left;
			free(root);
			return temp;
		}
		struct Node* temp = minValueNode(root->right);
		root->data = temp->data;
		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}

void inorder(struct Node* root)
{
	if(root != NULL)
        {
		inorder(root->left);
		printf("%d ", root->data);
                inorder(root->right);
        }
}

void preorder(struct Node* root)
{
	if(root != NULL)
        {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(struct Node* root)
{
	if(root != NULL)
        {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

int main()
{
	struct Node* root = NULL;
	root = insertNode(root, 50);
	insertNode(root, 20);
	insertNode(root, 70);
	insertNode(root, 15);
	insertNode(root, 65);
	insertNode(root, 20);
        insertNode(root, 75);
	printf("Inorder: ");
	inorder(root);
	printf("\n");
	printf("Preorder: ");
	preorder(root);
	printf("\n");
	printf("Postorder: ");
	postorder(root);
	printf("\n");
	int key = 65; /* Test with 90 whoch is not found in BST */
	if(searchNode(root, key))
		printf("%d is found in BST.\n", key);
	else
		printf("%d is not found in BST.\n", key);
        key = 50; /* Test with 50 which first  node of BST */
	deleteNode(root, key);
	printf("BST after deleting %d\n", key);
	inorder(root);
	printf("\n");
	return 0;
}	



