
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <malloc.h>


#define print printf
#define my_malloc malloc
#define NULL '\0'

typedef struct node
{
	int id;
	int size;
		 
}node;

typedef struct tree {

	tree *pa;
	tree *ch;
	tree *sib;
	node info;
}tree;


typedef struct _Q {

	tree *ptr;
}_Q;


//======================Globle Variables================

//Current Tree Pointer
tree *gtreeptr;
tree *root;
int qstart = 0;
int qend = 0;
_Q queue[100];

//=============Queue Operation===============
void InitQueue()
{
	qstart = 0;
	qend = 0;
	
}

void enqueue(tree *ptr)
{
	if (qend >= 100)
	{
		printf("Queue Overflow\n");
		return;
	}

	queue[qend++].ptr = ptr;

}
tree *dequeue()
{

	tree *retptr;
	if (qstart == qend) {
		printf("Queue Empty\n");
			return NULL;
	}
	return queue[qstart++].ptr;
}

int isQueueEmpty()
{
	if (qstart == qend)
		return 1;
	else
		return 0;

}

tree *GetNode(node data)
{

	tree *pNode = (tree*)my_malloc(sizeof(tree));

	pNode->pa = NULL;
	pNode->ch = NULL;
	pNode->sib = NULL;
	pNode->info.id = data.id;
	
	return pNode;
}


void AddSibling_Node(tree *treenode, node data,tree *curdir)
{
	
	printf("Add Sibling node: Id %d\n", data.id);
	
	//Traverse till end and insert the sibling node and parent information
	while (treenode->sib != NULL)
	{
		treenode = treenode->sib;
	}

	treenode->sib = GetNode(data);
	treenode->sib->pa = curdir;
	treenode->sib->ch = NULL;

}
void AddChild_Node(tree *root, node data)
{
	
	if (root == NULL)
		return;

	if (root->ch == NULL)
	{
		printf("Add Child node: Id %d\n", data.id);
		root->ch = GetNode(data);
		root->ch->pa = root;
		root->ch->sib =NULL;
		root->ch->ch = NULL;
	}
	else
	{
		AddSibling_Node(root->ch,data,root);
	}
}


void ChangeCurrentDir(tree *curptr)
{
	gtreeptr = curptr;
}

//DFS : Traversal : using recursion
//in DFS: apply recursive call on Child Node only
//sNode: Child Node of Given node 
void Traverse(tree *sNode)
{

	if (sNode == NULL)
		return;

	while (sNode != NULL)
	{

		//here Process the node
		print("id is %d\n", sNode->info.id);
		if (sNode->ch)
		{
			Traverse(sNode->ch);
		}
		sNode = sNode->sib;
	}
}

//BFS Traverse: Enqueue the Child Node and Process the Sibling Node
//child node of given node
void Traversal_BFS(tree *snode)
{

	if (snode != NULL)
		enqueue(snode);
	else
		return;

	while (!isQueueEmpty())
	{
		snode = dequeue();
		while (snode != NULL)
		{
			//Here is the Process the Node
			printf("Data is %d\n", snode->info.id);

			if (snode->ch)
			{
				enqueue(snode->ch);
			}
			snode = snode->sib;
		}
	}
}


tree *GetParentPointer(tree *child)
{

	printf("get parent pointer\n");
	
	if (child != NULL) {

		return child->pa;
	}
	else
		return NULL;

}

void Traverse_TillRootNode(tree *child)
{

	printf("Traverse back to Root Node and print all the data\n");

	while (child != root)
	{

		printf("Data is %d\n",child->info.id);
		child = child->pa;
	}
}

//BFS Traversal
//Required Queue for BFS traverasl...

void init()
{
	tree *pTree;
	node info;
	info.id = 0;

	pTree = GetNode(info);
	gtreeptr = pTree;
	InitQueue();
}

int main()
{

	print("N Tree Implementation Program\n");

	init();
	root = gtreeptr;

	node info;
	
	info.id = 1;
	AddChild_Node(gtreeptr, info);
	
	info.id = 2;
	AddChild_Node(gtreeptr, info);


	info.id = 3;
	AddChild_Node(gtreeptr, info);
	
	//change to  directory
	ChangeCurrentDir(gtreeptr->ch);

	info.id = 4;
	AddChild_Node(gtreeptr, info);

	info.id = 5;
	AddChild_Node(gtreeptr, info);

	//change to  directory
	ChangeCurrentDir(gtreeptr->ch);

	info.id = 6;
	AddChild_Node(gtreeptr, info);

	info.id = 7;
	AddChild_Node(gtreeptr, info);

	//change to  directory
	ChangeCurrentDir(gtreeptr->ch);

	info.id = 8;
	AddChild_Node(gtreeptr, info);

	info.id = 9;
	AddChild_Node(gtreeptr, info);

	Traverse(root);
	

	Traversal_BFS(root->ch);

	//Back travering from child to parent.
	Traverse_TillRootNode(gtreeptr);
	tree *parent_temp;

	parent_temp = GetParentPointer(gtreeptr);
	if (parent_temp != NULL)
		printf("Parent id is %d\n",parent_temp->info.id);

		_getch();
	return 0;
}
