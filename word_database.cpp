
#include <stdio.h>
#include <conio.h>

#define rint register int

#define MEM 1024*10*10
char mem[MEM];
long int allocation;
char pstr[27];


void *m_malloc(int size)
{
	allocation = allocation + size;
	return &mem[allocation - size];
}


typedef struct trienode{
	
	struct trienode *child[26];
	int eof;
	
}trienode;

trienode *root;
trienode *GetNode()
{
	trienode *pNode;
	rint i=0;
	pNode = (trienode*)m_malloc(sizeof(trienode));
	for(i=0;i<26;i++)	
		pNode->child[i]=NULL;
	
	pNode->eof = 0;	

	return pNode;
}


void add_node(char *str)
{
	
//	printf("Add Node %s\n",str);
	int index=0;
	trienode *pNode=root;
	rint i=0;
	
	for(i=0;str[i];i++)
	{
		
		index  = str[i] -'a';
		
		if(pNode->child[index] == NULL)	
		{
			pNode->child[index] = GetNode();
						
		}	
		pNode = pNode->child[index];
	}
	pNode->eof=1;	
}


void dfs_print(trienode *node, char *out_buf, int index)
{
	rint i;
	if(node->eof == 1)
	{
		out_buf[index] = '\0';
		printf("%s\n",out_buf); //output
	}

	for(i=0;i<26;i++)
	{
		if(node->child[i] != NULL)
		{
			out_buf[index] = i + 'a';
			dfs_print(node->child[i],out_buf,index+1);
		}
	}
}


void core_algo()
{
	rint i;
	int index;
	
	trienode *node = root;
	char out_buf[51];
	
	for(i=0;i<26;i++)
	{
		//get the trienode and run the dfs and print the string
		index = pstr[i] - 'a';
		if(node->child[index] != NULL)
		{
			out_buf[0]= index +'a';
			dfs_print(node->child[index],out_buf,1);
		}
	}
}


void init()
{
	allocation =0;
	root = GetNode();
}

int main()
{
	
	int tc;
	int T;
	int N;
	int num; //num of words in each test case	
	rint i,j,l; 

	char str[51];

	freopen("input.txt","r",stdin);
	
	scanf("%d",&N);
	scanf("%d",&tc);
	
	for(l=1;l<=tc;l++)
	{
		
		
		init();
		
		scanf("%s",pstr);
		scanf("%d",&num);
				
		for(j=0;j<num;j++)
		{
			scanf("%s",str);
			add_node(str);
		}
		printf("Test Case# %d\n",l);
		core_algo();		
	}
	_getch();
	return 0;	
}





