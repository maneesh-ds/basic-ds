#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <malloc.h>

typedef struct tree {
	int d;
	tree *l;
	tree *r;
}tree;

tree *root;

tree *GetNode(int n)
{
	tree *pNode = NULL;
	pNode = (tree*)malloc(sizeof(tree));
	pNode->d = n;
	pNode->l = NULL;
	pNode->r = NULL;
	return pNode;
}
tree *insert(tree *node, int n)
{
	if (node == NULL) 
	{
		node = GetNode(n);
		return node;
	}
	if (n < node->d)
	{
		node->l = insert(node->l, n);
	}
	else if (n > node->d)
	{
		node->r = insert(node->r, n);
	}
	return node;
}
void InsertNode(int n)
{
	printf("Insert node in BST %d\n",n);
	if (root == NULL)
		root = insert(root, n);
	else
		insert(root, n);
}

tree *search(tree *node, int n)
{
	if (node == NULL)
		return node;
	
	if (n == node->d)
	{
		printf("Node is found\n");
		return node;
	}
	if (n < node->d)
	{
		return search(node->l, n);
	}
	else if (n > node->d)
	{
		return search(node->r, n);
	}
}

void SearchNode(int n)
{	
	printf("Search Node %d\n",n);
	tree *res = search(root, n);
	if (res != NULL)
	{
		printf("Node value is %d\n", res->d);
	}
	else
		printf("Node is not found\n");
}

//Get the Minimum Node
tree *GetMinNode(tree *root)
{
	tree *pNode = root;
	if (pNode == NULL)
		return NULL;

	while (pNode->l != NULL)
	{
		pNode = pNode->l;
	}

	return pNode;
}
//Get the Maximum Node
tree *GetMaxNode(tree *root)
{
	tree *pNode = root;
	if (pNode == NULL)
		return NULL;

	while (pNode->r != NULL)
	{
		pNode = pNode->r;
	}

	return pNode;
}


tree *Delete(tree *node, int n)
{

	if (node == NULL)
		return node;

	if (n < node->d)
		node->l = Delete(node->l, n);
	else if (n > node->d)
		node->r = Delete(node->r, n);
	else if(n == node->d)
	{
		printf("Delete node is found\n", node->d);
		//Case 1 : //Lead node
		if (node->l == NULL && node->r == NULL)
		{
			node = NULL;
		}
		//Case :2 : Only Right Child
		else if (node->l == NULL)
		{
			node = node->r;
		}
		//Case :3 Only Left Child
		else if (node->r == NULL)
		{
			node = node->l;
		}
		//Case : 4 : Both Left and Child Available
		else 
		{
			//Get the Minimum node from right sub tree
			tree *minnode = GetMinNode(node->r);
			printf("Minmum node value %d\n",minnode->d);
			//Swap with current node value
			node->d = minnode->d;
			//remove the minimum node from right sub tree
			node->r = Delete(node->r, minnode->d);
		}
			
	}

	return node;
}

void DeleteNode(int n)
{
	printf("Delete Node is %d\n",n);
	Delete(root, n);

}

void Inorder(tree *node)
{
	if (node == NULL)
		return;
	
	Inorder(node->l);
	printf("Data is %d\n",node->d);
	Inorder(node->r);
}

int flag = 0;

tree *GetMidNode(tree *node, int size, int count)
{

	printf("count is %d\n",count);

	if (node == NULL)
		return node;

	if (count == (size / 2)) {
		flag = 1;
		return node;
	}
	GetMidNode(node->l, size, (count + 1));
	if (flag == 1)
		return node;

	GetMidNode(node->r, size, (count + 1));
	if (flag == 1)
		return node;

}

void init()
{
	root = NULL;
	flag = 0;
}
int main()
{
	printf("Dynamic Sort\n");
	init();

	InsertNode(50);
	InsertNode(30);
	InsertNode(20);
	InsertNode(40);
	InsertNode(70);
	InsertNode(60);
	InsertNode(80);
	
	Inorder(root);
	SearchNode(70);

	tree *minnode = GetMinNode(root);
	if (minnode)
		printf("Min node is %d\n",minnode->d);

	tree *maxnode = GetMaxNode(root);
	if (maxnode)
		printf("Max node is %d\n", maxnode->d);


	flag = 0;
	tree *midnode = GetMidNode(root,7,0);
	if (midnode)
		printf("Mid node is %d\n", midnode->d);

	_getch();
	return 0;
}