#include <stdio.h>
#include <conio.h>
#include <malloc.h>


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

		pNode->count = 1;
		pNode->eow = 0;
	}

	return pNode;
}


void AddTrie(char *str)
{
	int i;
	int index;

	trienode *pNode = root;

	for (i = 0;str[i];i++)
	{

		index = str[i] - 'a';
		if (pNode->child[index] == NULL)
		{
			pNode->child[index] = GetNode();

		}
		else
			pNode->child[index]->count++;


		pNode = pNode->child[index];
	}
	
	pNode->eow = 1;
}

//use DFS for print
void PrintTrie(trienode  *root,char *outstr, int index)
{
	int i = 0;

	trienode *pNode = root;


	for (i = 0;i < 26;i++)
	{
		if (pNode->child[i] != NULL)
		{
			outstr[index] = i + 'a';
			PrintTrie(pNode->child[i],outstr,index+1);
		}
	}
	if (pNode->eow)
	{
		outstr[index] = '\0';
		printf("str is %s,%d\n", outstr,pNode->count);
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

	printf("Searh STR is %s\n",str);

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

void PrepareTrie(char *str)
{
	int i = 0;
	for (i = 0;str[i];i++)
	{
		AddTrie(&str[i]);
	}
}


int main()
{
	
	char str[] = "maneesh";
	
	char outstr[11];
	int index = 0;

	root = GetNode();

	PrepareTrie(str);
	SearhTrie(str);
	PrintTrie(root,outstr,index);
	
	PrintTrie_allPossible(root, outstr, index);

	_getch();

	return 0;
}