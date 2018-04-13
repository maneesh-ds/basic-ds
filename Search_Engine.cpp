//Here we are learning... how we can reset the Large Array table on every new test case
// how we can reset the large Array table on every seach case
//One way.... add tesecase num in place use of 1



#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct idnode {

	struct idnode *next;
	int pageId;
	int isBlockId;

}idnode;


typedef struct stMap {

	int blockId;
	int removeId;
	int tc;
}stMap;


stMap map[50000];
int set[50000];
int testcase;

typedef struct trienode {

	struct trienode *child[26];
	int eow;
	int count;
	int isblock;

	idnode *node;

}trienode;


trienode *root;

trienode *GetTrieNode()
{
	int i;
	trienode *pNode;
	pNode = (trienode *)malloc(sizeof(trienode));

	if (pNode)
	{

		for (i = 0;i < 26;i++)
			pNode->child[i] = NULL;

		pNode->count = 0;
		pNode->eow = 0;
		pNode->isblock = 0;
		pNode->node = NULL;

	}
	return pNode;
}

idnode *GetIdNode(int mId)
{
	idnode *pNode = NULL;

	pNode = (idnode *)malloc(sizeof(idnode));

	if (pNode)
	{

		pNode->next = NULL;
		pNode->pageId = mId;
		pNode->isBlockId = 0;
	}
	return pNode;
}


void UpdateMapID(idnode *pNode, int block)
{

	while (pNode != NULL)
	{
		printf("Node id=%d, block=%d\n", pNode->pageId,block);
			if (block) {
			map[pNode->pageId].blockId++;
		}
		else {
			if(map[pNode->pageId].blockId > 0)
				map[pNode->pageId].blockId--;
		}

		pNode = pNode->next;
	}


}

idnode* SearchWord(char *str, int block)
{
	trienode *pNode = root;
	int index = 0;
	int i;

	//printf("Search Word is %s\n",str);
	idnode *pIdnode;

	for (i = 0;i < str[i];i++)
	{
		index = str[i] - 'a';

		if (pNode->child[index] == NULL)
		{
			//printf("Word not found\n");
			return NULL;
		}
		pNode = pNode->child[index];
	}

	if (pNode != NULL && pNode->eow)
	{
		printf("word is found : Num of Word %d\n",pNode->count);
		pIdnode = pNode->node;

		//Ignore in case normal mode
		if (block <  2)
			pNode->isblock = block;

		return pIdnode;
	}
	return NULL;

}


void AddPageID(trienode *pNode, int mID)
{
	
	idnode *pIdNode;

	//Update the Page ID List
	pIdNode = GetIdNode(mID);


	if (map[mID].tc != testcase)
	{
		map[mID].removeId = 0;
		map[mID].blockId = 0;
		map[mID].tc = testcase;
	}

	
	printf("Isblock [%d]-> %d\n",mID,pNode->isblock);

	//Check if Node is bloced or not
	if (pNode->isblock) {
		//update the map table
		map[mID].blockId++;
	}
	if (pNode->node == NULL)
	{
		pNode->node = pIdNode;
	}
	else
	{
		pIdNode->next = pNode->node;
		pNode->node = pIdNode;
	}


}

//Add the word in Trie DS and maintain the pageID
void AddWord(char *str, int mID)
{
	int i = 0;
	int index;
	trienode *pNode = root;
	
	//printf("Page ID %d,String is %s\n",mID,str);

	for (i = 0;str[i];i++)
	{
		index = str[i] - 'a';

		if (pNode->child[index] == NULL)
		{
			pNode->child[index] = GetTrieNode();
		}

		pNode = pNode->child[index];
	}

	//End of World Reach
	pNode->eow = 1;
	pNode->count++;

	if (mID == -1)
		pNode->isblock = 1;

	//Add the Page ID, ignore in case add Blockword 
	if (mID != -1) {
		AddPageID(pNode, mID);
	}

}

int SearchMode(char word[][11], int mode)
{
	//Add here the Search Logic
	// Reset the Set Table after each Search

	idnode *pNode;
	int count = 0;
	int id = 0;
	if (mode == 0)
	{
		//Normal Mode.. return the count
		pNode = SearchWord(word[0],2);

		while (pNode != NULL)
		{
			id = pNode->pageId;
			//check if given ID is blocked or removed
			if (map[id].tc == testcase)
			{
				if ((map[id].blockId == 0) && (map[id].removeId == 0))
				{
					count++;
				}
			}
			pNode = pNode->next;
		}

	}
	else if (mode == 1)
	{
		printf("And Case\n");
		idnode *temp;
		idnode *pNode2;
		count = 0;
		//use the SET Table for the same.
		pNode = SearchWord(word[0], 2);
		int id;
		temp = pNode; //for reseting the SET Table
		//update the SET 
		while (pNode != NULL)
		{
			set[pNode->pageId] = 1;
			pNode = pNode->next;
		}

		//Now Search Another word
		pNode2 = SearchWord(word[1], 2);
		//In case And mode, if Id found in SET Table, increase the count
		while (pNode2 != NULL)
		{

			id = pNode2->pageId;
			//check for removeID & Block ID Case Also
			if (map[id].tc == testcase)
			{
				if ((map[id].removeId == 0) && (map[id].blockId == 0))
				{
					//if ID was found in first search, increase the count by 1
					if (set[id] == 1)
					{
						count++;
					}
				}
			}
			pNode2 = pNode2->next;
		}

		//Last Step... Reset the SET Table....to avoid the any collision
		//Use the Temp for the same to avoid the search again.
		while (temp != NULL)
		{
			set[temp->pageId] = 0;
			temp = temp->next;
		}

	}

	else if (mode == 2)
	{
		printf("OR Case\n");
		idnode *temp;
		idnode *pNode2;
		count = 0;
		//use the SET Table for the same.
		pNode = SearchWord(word[0], 2);
		temp = pNode; //for reseting the SET Table
					  //update the SET 
		while (pNode != NULL)
		{
			
			id = pNode->pageId;
			//check for removeID & Block ID Case Also
			if (map[id].tc == testcase)
			{
				if ((map[id].removeId == 0) && (map[id].blockId == 0))
				{
					count++;
					set[pNode->pageId] = 1;
				}
			}
			pNode = pNode->next;
		}

		//Now Search Another word
		pNode2 = SearchWord(word[1], 2);
		//In case And mode, if Id found in SET Table, increase the count
		while (pNode2 != NULL)
		{
			id = pNode2->pageId;
			//check for removeID & Block ID Case Also
			if (map[id].tc == testcase)
			{
				if ((map[id].removeId == 0) && (map[id].blockId == 0))
				{
					if (set[id] != 1)
					{
						count++;
					}
				}
			}
			pNode2 = pNode2->next;
		}

		//Last Step... Reset the SET Table....to avoid the any collision
		//Use the Temp for the same to avoid the search again.
		while (temp != NULL)
		{
			set[temp->pageId] = 0;
			temp = temp->next;
		}


	}
	return count;
}
void RemoveID(int mID)
{
	printf("Remove ID Test case %d, mID is %d\n", testcase, mID);
	map[mID].removeId = 1;
	map[mID].tc = testcase;
	map[mID].blockId = 0;
}

void RecoverWord(char *str)
{
	idnode *pNode;
	pNode = SearchWord(str, 0);
	if (pNode)
	{
		//At same time, update the all the Page IDs in Map Tab;e
		UpdateMapID(pNode, 0);
	}

}
void BlockWord(char *str)
{
	idnode *pNode;

	printf("Block word :%s\n",str);
	pNode = SearchWord(str,1);

	if (pNode)
	{
		//At same time, update the all the Page IDs in Map Tab;e
		UpdateMapID(pNode, 1);
	}
	else
	{
		printf("Word not found in list\n");
		//Add the Word in Trie without any node in list
		AddWord(str,-1);
	}
}
void init(int N)
{
	root = GetTrieNode();
	if (!root)
		printf("Memorty issue\n");
	//How to reset the removeID Array
	testcase++;
}	
int main()
{

	int N;
	int i;
	int mode = 0;
	char str1[] = "abcd";
	char str2[] = "cdef";
	char str3[] = "cdefs";
	char str4[] = "abcddf";
	char str5[] = "maneesh";

	char word[][11] = {"cdef","cdef"};
	int res = 0;

	for (i = 0;i < 2;i++)

	{
		init(0);

		AddWord(str1, 0);
		BlockWord(str2);
		RecoverWord(str2);

		AddWord(str2, i+1);
		AddWord(str2, i+2);
		AddWord(str2, i+3);
		AddWord(str2, i+4);

		//	BlockWord(str5);
		//	BlockWord(str3);

		res = SearchMode(word, 0);
		printf("Answer is %d\n", res);
		RecoverWord(str2);
		RemoveID(2);

		res = SearchMode(word, 0);
		printf("Answer is %d\n", res);

	}
	_getch();
	return 0;

}