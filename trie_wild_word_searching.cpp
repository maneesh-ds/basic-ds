#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>


// Print all Possible occurance of given string 
typedef struct trienode {

	struct trienode *child[26];
	int count;
	int eow;

}trienode;

trienode *root;

trienode* GetNode()
{
	trienode *pNode;
	int i = 0;
	pNode = (trienode*)malloc(sizeof(trienode));
	if (pNode)
	{
		for (i = 0;i < 26;i++)
			pNode->child[i] = NULL;
		pNode->count = 0;
		pNode->eow = 0;
	}

	return pNode;
}


void AddTrie(char *str)
{
	int i;
	int index;
	printf("Add Trie %s\n",str);
	trienode *pNode = root;
	for (i = 0;str[i];i++)
	{
		index = str[i] - 'a';
		if (pNode->child[index] == NULL)
		{
			pNode->child[index] = GetNode();

		}
		pNode->child[index]->count++;

		pNode = pNode->child[index];
	}

	pNode->eow = 1;
}

//use DFS for print
void PrintTrie(trienode  *root, char *outstr, int index)
{
	int i = 0;
	trienode *pNode = root;

	for (i = 0;i < 26;i++)
	{
		if (pNode->child[i] != NULL)
		{
			outstr[index] = i + 'a';
			PrintTrie(pNode->child[i], outstr, index + 1);
		}
	}
	if (pNode->eow)
	{
		outstr[index] = '\0';
		printf("str is %s,%d\n", outstr, pNode->count);
	}
}

//use DFS for print to all possible combination
void PrintTrie_allPossible(trienode  *root, char *outstr, int index)
{
	int i = 0;

	trienode *pNode = root;


	for (i = 0;i < 26;i++)
	{
		if (pNode->child[i] != NULL)
		{
			outstr[index] = i + 'a';
			PrintTrie_allPossible(pNode->child[i], outstr, index + 1);
		}
	}
	if (index > 0) {
		outstr[index] = '\0';
		printf("str is %s,%d\n", outstr, pNode->count);
	}
}
int SearhTrie(char *str)
{

	int i;
	int index;

	trienode *pNode = root;

	printf("Searh STR is %s\n", str);

	for (i = 0;str[i];i++)
	{
		index = str[i] - 'a';
		if (pNode->child[index] == NULL)
			return 0;
		pNode = pNode->child[index];

	}
	if (pNode && pNode->eow)
	{
		printf("world is found\n");
		return 1;
	}
	return 0;
}

char g_str[20];
void wild_with_prefix(trienode *root,char *outstr,int out_index,int count)
{
	int i = 0;
	int index = 0;;
	for (i = 0;i < 26;i++)
	{
		if (g_str[count] == '*')
		{
			if (root->child[i] != NULL)
			{
				outstr[out_index] = i + 'a';
				wild_with_prefix(root->child[i], outstr, out_index + 1, count + 1);
			}
			else
				continue;
		}
		else
		{
			index = g_str[count] - 'a';
			if (index < 0)
				continue;
			if (root->child[i] != NULL)
			{
				if (i == index) 
				{
					outstr[out_index] = i + 'a';
					wild_with_prefix(root->child[i], outstr,out_index+1,count+1);
				}
				else
					continue;
			}
		}
	}
	if (root->eow)
	{
		int len = strlen(g_str);
		if (count == len)
		{
			outstr[out_index] = '\0';
			printf("str is %s,%d\n", outstr, root->count);
		}
	}
}
void PrintSpecificWord(char *str)
{

	strcpy(g_str, str);
	char out_str[20];
	wild_with_prefix(root, out_str, 0, 0);
}
void init()
{
	root = GetNode();
}
int main()
{

	char str[20];
	char outstr[20];
	int index = 0;
	int i,N,cmd;
		
	init();
	freopen("input.txt","r",stdin);

	scanf("%d", &N);
	for(i=0;i<N;i++)
	{
		scanf("%d",&cmd);
		switch (cmd)
		{
			case 1:
			{
				scanf("%s", str);
				AddTrie(str);
				break;
			}
			case 2:
			{
				PrintTrie(root, outstr, 0);
				break;
			}
			case 3:
			{
				scanf("%s", str);
				printf("print all the words as part of given sub str %s\n",str);
				PrintSpecificWord(str);
				break;
			}
			case 4:
			{
				scanf("%s", str);
				SearhTrie(str);
				break;
			}
		}
	}
	_getch();

	return 0;
}