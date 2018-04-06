
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//Its contain actual information
typedef struct node {

	int key; //used to generate the index
	int age;
	char name[100];
	struct node *next;

}node;

typedef struct hashmap {
	struct node *head;
	int count;
}hashmap;

//Define the Hash Table Size
struct hashmap hashtable[7];

int hashvalue = 7;

node *GetDataNode(int key, char name[], int age)
{

	node *pNode;
	pNode = (struct node*)malloc(sizeof(node));
	
	if (pNode != NULL)
	{
		pNode->age = age;
		pNode->key = key;
		strcpy_s(pNode->name, name);
		pNode->next = NULL;
	}
	return pNode;
}

void insertToHash(int key,char name[],int age)
{
	
	int index = 0;
	
	//Generate the Index using Key Value.
	index = key % hashvalue;

	node *pNode = GetDataNode(key,name,age);

	//if no item in given index,add the node
	if (hashtable[index].head == NULL) 
	{
		hashtable[index].head = pNode;
		hashtable[index].count = 1;
		return;
	}
	
	pNode->next = hashtable[index].head;
	//update the head and count
	hashtable[index].head = pNode;
	hashtable[index].count++;
	return;

}


void DisplayNode()
 {
	int i = 0;

	node *pNode;

	for (i = 0;i < hashvalue;i++)
	{	
		if (hashtable[i].count == 0)
			continue;
		
		pNode = hashtable[i].head;
		printf("\nData at index %d in Hash Table:\n", i);
		printf("VoterID     Name          Age   \n");
		printf("--------------------------------\n");

		while (pNode != NULL)
		{
			printf("%-12d", pNode->key);
			printf("%-15s", pNode->name);
			printf("%d\n", pNode->age);
			pNode = pNode->next;
		}
	}
}

void DeleteNode(int key)
{
	int index = 0;
	
	index = key % hashvalue;
	node *pNode = NULL;
	node *pTemp = NULL;

	if (hashtable[index].count > 0)
	{
		printf("Node may available to delete....\n");
		pNode = hashtable[index].head;
		pTemp = pNode;

		while (pNode != NULL)
		{
			//In case first Node to be delete...
			if (pNode->key == key)
			{
				//check if it is first node
				if (pNode == hashtable[index].head)
				{
					printf("Delete First Node\n");
					hashtable[index].head = pTemp->next;
				}
				else {
					printf("Delete other Node\n");
					pTemp->next = pNode->next;
				}
				hashtable[index].count--;
				free(pNode);
				return;
			}
			pTemp = pNode;
			pNode = pNode->next;
		}
	}
}

int SearchHash(int key)
{

	printf("Search the key : %d\n",key);

	int index = 0;
	node *pNode = NULL;
	index = key % hashvalue;

	//Handle the Chaining Collosion
	if (hashtable[index].count > 0)
	{

		pNode = hashtable[index].head;
		while (pNode != NULL)
		{
			if (pNode->key == key) 
			{
				printf("VoterID     Name          Age   \n");
				printf("--------------------------------\n");
				printf("%-12d", pNode->key);
				printf("%-15s", pNode->name);
				printf("%d\n", pNode->age);
				return 1;
			}
			pNode = pNode->next;
		}
		return 0;
	}
	else
		return 0;
}

int main()
{

	int i, j;
	int key, age;
	char name[100];
	int ch = 0;
	int is_exit = 0;

	while (1)
	{

		printf("\n1. Insertion\t2. Deletion\n");
		printf("3. Searching\t4. Display\n5. Exit\n");
		printf("Enter your choice:");
		scanf_s("%d", &ch);
		switch (ch) {
		
			case 1:
				printf("Insert the Item in Hash\n");
				printf("Enter the key value:");
				scanf_s("%d", &key);
				getchar();

				printf("Name:");
				fgets(name, 100, stdin);
				name[strlen(name) - 1] = '\0';
				
				printf("Age:");
				scanf_s("%d", &age);
				insertToHash(key, name, age);
				break;

			case 2:
				printf("Delete the Item from Hash\n");
				scanf_s("%d", &key);
				DeleteNode(key);

				break;

			case 3:
				printf("Search the Item in Hash.....\n");
				scanf_s("%d", &key);
				printf("Key Found results %d\n",SearchHash(key));
				break;

			case 4:
				printf("Display the Hash\n");
				DisplayNode();
				break;
		

			case 5:
				printf("Exit...\n");
				is_exit = 1;

		}
		if (is_exit)
			break;
	}
	return 0;

}

