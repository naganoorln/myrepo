#include <stdio.h>
#include <stdlib.h>
struct Node
{
	int data;
	struct Node* next;
};
void createNode(struct Node** head, int data)
{
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = data;
	newnode->next = NULL;
	if((*head) == NULL)
	{
		(*head) = newnode;
		return;
	}
	struct Node* temp = (*head);
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
}
void printList(struct Node* head)
{
	while(head)
	{
		printf("%d ",head->data);
		head = head->next;
	}
	printf("\n");
}
struct Node* mergeLists(struct Node* L1, struct Node* L2)
{
	struct Node dummay;
	struct Node* tail = &dummay;
	dummay.next = NULL;
	while(L1 && L2)
	{
		if(L1->data < L2->data)
		{
			tail->next = L1;
			L1 = L1->next;
		} else {
			tail->next = L2;
			L2 = L2->next;
		}
		tail = tail->next;
	}
	if(L1 != NULL)
	{
		tail->next = L1;
	} else {
		tail->next = L2;
	}
	return dummay.next;
}
int main()
{
	struct Node* L1 = NULL;
	struct Node *L2 = NULL;
	createNode(&L1, 2);
	createNode(&L1, 4);
	createNode(&L1, 7);
	printf("List L1: ");
	printList(L1);
	createNode(&L2, 3);
	createNode(&L2, 5);
	createNode(&L2, 6);
	printf("List L2: ");
	printList(L2);
    struct Node* mlist = mergeLists(L1, L2);
    printf("Merged List[L1 and L2]: ");
    printList(mlist);
	return 0;
}