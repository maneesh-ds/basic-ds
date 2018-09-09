
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <malloc.h>

#define rint register int;

//BST Operation of tree 
//1. Get the height of Tree: Maintain it
//2. Handle the Parent of Tree

#define LEFT 1
#define RIGHT 2


//Keep Parent node with BST .. it helps in travesal from leaf to its parent.
typedef struct tree {
	int d;
	tree *l;
	tree *r;
	tree *p;
	int rank;
	int h; //depth of tree
	int type; //left node or right node
}tree;

tree *root;

tree *GetNode(int n)
{
	tree *pNode = NULL;
	pNode = (tree*)malloc(sizeof(tree));
	pNode->d = n;
	pNode->l = NULL;
	pNode->r = NULL;
	pNode->p = NULL;
	pNode->h = 0;
	pNode->rank = 0;
	pNode->type = 0;
	return pNode;
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

//Rank is used the calulate the number of childrens of a given node (Left + Right)
tree *insert_node(int n, tree *root)
{

	//printf("insert node is %d\n", n);
	int flag = 0;
	tree *prev = root;
	tree *pNode = root;

	while (pNode != NULL)
	{
		prev = pNode;
		if (n <= pNode->d)
		{
			pNode->rank++;
			pNode = pNode->l;
		}
		else {
			//pNode->rank++;
			pNode = pNode->r;
			
		}
	}

	if (root == NULL) {
		root = GetNode(n);
	}

	else if (n < prev->d)
	{
		prev->l = GetNode(n);
		prev->l->p = prev;
		prev->l->type = LEFT;
	}
	else
	{
		prev->r = GetNode(n);
		prev->r->p = prev;
		prev->r->type = RIGHT;

	}
	return root;
}

//update the rank after delete as well
// first check if element is available
// then delete it


void InsertNode(int n)
{
	printf("Insert node in BST %d\n",n);
	root = insert_node(n,root);
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


tree *del_ptr;
int del_flag = 0;
tree *Delete(tree *node, int n)
{

	tree *temp = NULL;
	if (node == NULL)
		return node;

	if (n < node->d) {
		node->l = Delete(node->l, n);
	}

	else if (n > node->d) {
		node->r = Delete(node->r, n);
	}
	else if(n == node->d)
	{
		printf("Delete node is found\n", node->d);
		if (del_flag == 0) {
			del_ptr = node;
			del_flag = 1;
		}
		//printf("delete node : first %d, end %d\n",first, current);
		//Case 1 : //Lead node
		if (node->l == NULL && node->r == NULL)
		{
			printf("No children\n"); //no need to update the parent
			node = NULL;
		}
		//Case :2 : Only Right Child
		else if (node->l == NULL)
		{
			printf("right node\n");
			temp = node->p;
			node = node->r;
			node->p = temp;  //parent node needs to updates

		}
		//Case :3 Only Left Child
		else if (node->r == NULL)
		{
			printf("left node\n");
			//I think parent node needs to be update as wells
			temp = node->p;
			node = node->l;
			node->p = temp;

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
	tree *parent;
	tree *node = del_ptr;
	printf("Delete Node is %d\n",n);
	root = Delete(root, n);

	printf("type of delete node %d, value %d\n",del_ptr->type, del_ptr->d);
	
	if (del_ptr) 
	{
		parent = del_ptr->p;
		if (parent == NULL)
			printf("Root node is delete.... no change in Rank\n");
		else
		{
			while(parent != NULL)
			{
				if (node->type == LEFT)
					parent->rank--;
				node = parent;
				parent = parent->p;
			}
		}
	}
	else
		printf("node is not available to delete\n");

}

void Inorder(tree *node)
{
	if (node == NULL)
		return;
 	
	Inorder(node->l);

	printf("Data is %d, Rank of Node %d\n", node->d,node->rank);

	Inorder(node->r);
}

tree *GetKthMax(tree *node, int cnt)
{
	if (node == NULL)
	{
		printf("kth num is not available\n");
		return NULL;
	}
	if (cnt < (node->rank + 1))
		GetKthMax(node->l, cnt);

	else if (cnt > (node->rank + 1))
		GetKthMax(node->r, (cnt - 1 - node->rank));

	else
	{
		//printf("Node is found %d\n", node->d);
		return node;
	}
}
tree *GetKthMax_iteration(tree *node, int cnt)
{
	while (node != NULL)
	{
		printf("count is %d\n",cnt);
		if (cnt == (node->rank + 1))
		{
			printf("Node is found %d\n", node->d);
			return node;
		}
		else if (cnt < (node->rank + 1))
		{
			node = node->l;
		}
		else if (cnt > (node->rank + 1))
		{
			cnt = cnt - 1 - node->rank;
			node = node->r;
		}
	}
	return node;
}
int fnt = 0;
int  GetRange(tree *node, int s, int e)
{
	if (node == NULL)
		return fnt;
	//printf("GetRange : %d %d-->%d\n", s, e, node->d);
	if (node->d < s && node->d < e)
	{
		//printf("Only right side\n");
		GetRange(node->r, s, e);
	}

	else if (node->d > s && node->d > e)
	{
		//printf("Left side only\n");
		GetRange(node->l, s, e);
	}
	else
	{
		//printf("Both side\n");
		GetRange(node->l, s, e);
		GetRange(node->r, s, e);
		fnt++;
	}

}

tree *lowptr=NULL;
tree *highptr=NULL;
tree *resptr=NULL;
int low = -1;
int high = -1;
void UpdateLowHigh(tree *node, int id)
{
	printf("high %d low %d\n", high, low);
	if (node != NULL)
	{
		if (node->d < id)
		{
			if (low == -1) {
				low = node->d;
				lowptr = node;
			}
			else
			{
				if (low < node->d) {
					low = node->d;
					lowptr = node;
				}
			}
		}
		else
		{
			if (high == -1) {
				high = node->d;
				highptr = node;
			}
			else
			{
				if (high < node->d) {
					high = node->d;
					highptr = node;
				}
			}
		}
	}

}
void Search_node_closest(tree *node, int sId)
{

	tree *pNode = node;
	int data;
	printf("Search id is %d\n",sId);


	while (pNode != NULL)
	{
		UpdateLowHigh(pNode, sId);

		if (sId == pNode->d)
		{
			printf("Found the same id %d\n", pNode->d);
			resptr = pNode;
			return;
		}

		else if (sId < pNode->d)
		{
			printf("Left side : %d, low : %d\n", pNode->d,low);
			pNode = pNode->l;
		}
		else
		{
			printf("right side %d, high %d\n", pNode->d,high);
			pNode = pNode->r;
		}
	}
}


void init()
{
	root = NULL;
//	flag = 0;
}
int main()
{
	printf("Dynamic Sort\n");
	init();
	int i;

	int N = 0; //num of operation
	int cmd;
	int v;
	freopen("input.txt","r",stdin);

	scanf("%d",&N);

	for (i = 0;i < N;i++)
	{
		scanf("%d", &cmd);

		switch (cmd)
		{
		case 1:
		{
			printf("Insert  Command \n");
			scanf("%d", &v);
			InsertNode(v);
			break;
		}
		case 2:
		{
			printf("Delete Command :\n");
			scanf("%d", &v);
			DeleteNode(v);
			break;
		}
		case 3:
		{
			printf("In Order Command : Sort : Ascending\n");
			Inorder(root);
			break;
		}
		case 4:
		{
			printf("Post Order : Sort : Descending\n");
			//
			int w;
			scanf("%d %d",&v,&w);
			int ret = GetRange(root, v, w);
			printf("conut is %d\n", ret);
			break;
		}
		case 5:
		{
			printf("Get Mid ...\n");
			scanf("%d", &v);
			tree *mid = GetKthMax_iteration(root,v);
			if(mid)
				printf("Mid node is %d\n", mid->d);

			break;
		}
		case 6:
		{
			printf("Get Max ....\n");
			tree *max = GetMaxNode(root);
			printf("Max node is %d\n", max->d);
			break;

		}
		case 7:
		{
			scanf("%d", &v);
			printf("Find the closest match %d\n",v);

			Search_node_closest(root, v);
			int d1=-1, d2=-1;
			int d;

			printf("low %d , high %d\n",low,high);

			if (resptr==NULL)
			{
				if (low != -1) 
					d1 = v - low;
				if (high != -1)
					d2 = high - v;

				if (d1 == -1)
					resptr = highptr;
				else if (d2 == -1)
					resptr = lowptr;
				else if (d1 < d2)
					resptr = lowptr;
				else if(d1 > d2 )
					resptr = highptr;
				else if (d1 == d2)
				//choose the lowest one
					resptr = lowptr;

				printf("d1=%d, d2=%d\n",d1,d2);
			}
		
			printf("Closet num is %d\n",resptr->d);

			break;


		}

	  }
	}

	_getch();
	return 0;
}


