#include <stdio.h>
#include <conio.h>
#include <malloc.h>

typedef struct node {

	struct node *next;
	int data;
	
}node;


node *root = NULL;

node* GetNode(int v)
{
	
	node *pNode;
	pNode = (node *)malloc(sizeof(node));
	if (pNode)
	{
		pNode->data = v;
		pNode->next = NULL;
		return pNode;
	}
	return NULL;
}


void InsertNode(int v)
{
	node *pNode = NULL;
	pNode = GetNode(v);
	pNode->next = root;
	root = pNode;
}

void DeleteNode(int v)
{
	node *pNode = root;
	node *pTemp = pNode;

	while (pNode != NULL)
	{
		if (pNode->data == v)
		{
			printf("Node.. found to be delete\n");
			//if first node
			if (pNode == root)
			{
				printf("Delete First node\n");
				root = pNode->next;
				free(pNode);
				return;
			}
			else
			{
				printf("Delete another nodes\n");
				pTemp->next = pNode->next;
				free(pNode);
				return;
			}
		}
		pTemp = pNode;
		pNode = pNode->next;
	}
}

void PrintNode()
{
	int i = 0;

	node *pNode = root;
	while (pNode != NULL)
	{
		printf("Date is %d\n", pNode->data);
		pNode = pNode->next;
	}

}

int main()
{

	printf("Link List Program\n");
	int n = 0;
	int v = 0;

	while (1) {
	
		printf("Input the option....\n");

		scanf_s("%d", &n);

		switch (n)
		{
		case 1:
			printf("Add Node\n");
			scanf_s("%d", &v);
			InsertNode(v);
			break;
		case 2:
			printf("Delete Node\n");
			scanf_s("%d", &v);
			DeleteNode(v);
			break;
		case 3:
			printf("Print Node\n");
			PrintNode();
			break;

		case 4:
			printf("exit the program\n");
			return 0;

		default:
			break;
		}
	}
	_getch();
	return 0;
}
