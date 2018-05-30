#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <malloc.h>


#define CHILD_MAX 20
#define TREE_NODE 15010

#define print printf

typedef struct _sttree {

	int parent;
	int child[CHILD_MAX];
	int db_id;
	int tc;
}_sttree;

_sttree tree[TREE_NODE];


int gtestcase;


void AddNode_Tree(int parent, int child,int db_index)
{
	
	print("Add node %d %d\n",parent,child);
	register int i = 0;

	for (i = 0;i < CHILD_MAX;i++)
	{
		if (tree[parent].child[i] == 0)
			break;
	}

	tree[parent].child[i] = child;
	tree[child].parent = parent;
	tree[child].db_id = db_index;
}


//Traverse using Pre-order (data, leftindex and right index
void Traverse_Tree(int index)
{
	printf("Data is %d-> %d\n",index,tree[index].db_id);

	for (register int i = 0;i < CHILD_MAX;i++)
	{
		if (tree[index].child[i] != 0)
		{
			Traverse_Tree(tree[index].child[i]);
		}

	}
}

int flag = 0;
void Search_Tree(int data, int index)
{

	if (flag == 1)
		return;

	if (tree[index].db_id == data) {
		printf("found the data: node is %d\n",index);
		printf("parent of index is %d\n",tree[index].parent);
		flag = 1;
		return;
	}
	
	for (register int i = 0;i < CHILD_MAX;i++)
	{
		if (tree[index].child[i] != 0)
		{
			Search_Tree(data, tree[index].child[i]);
		}
	}
}


int main()
{

	int opr = 0;
	int testcase;
	int loop_out = 0;

	int k = 0;

	freopen("input.txt", "r", stdin);
	scanf("%d", &testcase);

	char str[50];
	for (register int i = 0;i < testcase;i++)
	{


		loop_out = 0;

		while (loop_out != 1)
		{
			scanf("%d", &opr);
			//print("Operation is %d\n", opr);
			switch (opr)
			{
				//Add Node in Heap
			case 1:
			{
				int parent;
				int child, id;
				scanf("%d %d %d",&parent,&child,&id);
				AddNode_Tree(parent,child,id);
				break;
			}
			//Display
			case 2:
			{
				int traverse_node = 0;
				scanf("%d", &traverse_node);
				Traverse_Tree(traverse_node);
				break;
			}

			case 3:
			{
				int data;
				int parent;
				scanf("%d %d",&parent,&data);
				Search_Tree(parent, data);
				break;
			}

			case 0:
			{
				printf("exit\n");
				loop_out = 1;
				_getch();
				break;
			}
			}
		}
	}

	
	_getch();
	return 0;
}