/*
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <malloc.h>

typedef struct trienode {


	struct  trienode *child[26];
	int eow;
	int count;


}trienode;


trienode *root = NULL;

trienode* GetNode()
{

	trienode *pNode = NULL;

	pNode = (trienode *)malloc(sizeof(struct trienode));

	if (pNode != NULL)
	{

		for (register int i = 0;i < 26;i++)
		{

			pNode->child[i] = NULL;
		}
		pNode->eow = 0;
		pNode->count = 0;
	}

	return pNode;
}


void Init()
{

	root = GetNode();

}

void AddNode(char *str)
{

	int index = 0;
	int i = 0;
	trienode *pNode = root;
	printf("String to be add %s\n",str);
	for (i = 0;str[i];i++)
	{

		index = str[i] - 'a';

		if (pNode->child[index] == NULL)
		{
			pNode->child[index] = GetNode();
			pNode->count++;
		}
		else
		{
			pNode->count++;
		}
		pNode = pNode->child[index];

	}

	pNode->eow = 1;
	pNode->count++;

}

trienode *SearchNode(char *str)
{
	int index = 0;
	trienode *pNode = root;

	for (register int i = 0;str[i];i++)
	{

		index = str[i] - 'a';

		if (pNode->child[index] == NULL)
		{
			return NULL;
		}
		pNode = pNode->child[index];

	}

	if (pNode != NULL && pNode->eow)
	{
		printf("Word is found n");
		return pNode;
	}

	return NULL;
}


//Print the Words Available in Trie Node

void PrintTrie(trienode *root,char *outstr, int index)
{

	int i;

	trienode *pNode = root;

	for (i = 0;i < 26;i++)
	{
		
		if (pNode->child[i] != NULL)
		{

			outstr[index] = i + 'a';
			PrintTrie(pNode->child[i], outstr, index + 1);
		}

	}

		if (pNode->eow == 1) {
			outstr[index] = '\0';
			printf("word is %s\n", outstr);
		}
}



void SearchNodeinTrie(char *str)
{

	trienode  *pNode;

	pNode = SearchNode(str);

	if (pNode != NULL)
	{

		printf("Word is found : count %d\n", pNode->count);

	}
	else
		printf("word is not found\n");

}

int main()
{
	 
	printf("Trie Node implementation\n");

	int testcase = 0;
	int loop_out = 0;
	int opr;
	char str[30];

	freopen("input.txt","r",stdin);
	scanf("%d",&testcase);
	printf("test case  is %d\n", testcase);

	for (register int i = 0;i < testcase;i++)
	{
		Init();
		loop_out = 0;
		while (loop_out != 1)
		{

			scanf("%d",&opr);
			printf("operation is %d\n",opr);
			switch (opr)
			{
				case 1:
				{
					scanf("%s",str);
					AddNode(str);
					break;
				}
				case 2:
				{
					scanf("%s", str);
					SearchNodeinTrie(str);
					break;
				}
				case 3:
				{
					printf("Display the Trie\n");
					char outstr[30];
					PrintTrie(root, outstr, 0);
					break;
				}
				case 0:
				{
					loop_out = 1;
					break;

				}

			}

		}
		_getch();

	}



	_getch();

	return 0;
}
*/