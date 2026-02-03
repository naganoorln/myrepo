/* BST */
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *left, *right;
};

struct Node* newnnode(int value)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = value;
	node->left = node->right = NULL;
	return node;
}

struct Node* insertnode(struct Node* root, int value)
{
	if(root == NULL)
		return newnnode(value);
	if(value < root->data)
		root->left = insertnode(root->left, value);
	else if(value > root->data)
		root->right = insertnode(root->right, value);
	return root;
}

struct Node* serchnode(struct Node* root, int key)
{
	if(root == NULL | root->data == key)
		return root;
	if(key < root->data)
		return serchnode(root->left, key);
	else if(key > root->data)
		return serchnode(root->right, key);
}

struct Node* minValueNode(struct Node* node)
{
	struct Node* current = node;
	while(current && current->left != NULL)
		current = current->left;
	return current;
}
struct Node* deletenode(struct Node* root, int key)
{
	if(root == NULL)
		return root;
	if(key < root->data)
		root->left = deletenode(root->left, key);
	else if(key > root->data)
		root->right = deletenode(root->right, key);
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
		root->right = deletenode(root->right, temp->data);

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
	root = insertnode(root, 50);
	insertnode(root, 20);
	insertnode(root, 70);
	insertnode(root, 30);
	insertnode(root, 60);
	insertnode(root, 10);
	insertnode(root, 80);
	printf("Inorder:");
	inorder(root);
	printf("\n");
	printf("Preorder:");
	preorder(root);
	printf("\n");
	printf("Postorder:");
	postorder(root);
	int key = 60;
	if(serchnode(root, key))
		printf("\n%d is found in BST.\n", key);
	else
		printf("%d is not found in BST.\n", key);
	key = 50;
	deletenode(root, key);
	printf("Inorder of BST after deleteing %d:", key);
	inorder(root);
	return 0;
}