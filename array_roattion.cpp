#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<conio.h>

#define MAXN 4
#define BSIZE 4
#define rint register int

int db[MAXN*MAXN][BSIZE][BSIZE];

typedef struct block {

	int ownid;
	long ownseq;
	long nseq;
}block;

block blk[MAXN*MAXN][4];




//Steps
// 1. Extract the block
// 2. Prepare the Blocks by calulate the own value and neighour value for all four direction.
// 3. Prepare the mapping table
//4. Find the corners 
//5. start fitting it
//1234
// 1 2 3 4 

//1234

// 1*0 + 1 : 1
//1*10+2 : 12
// 12*10 + 3 : 123
// 123*1000+4 = 1234

long GetOwn(int id, int dir)
{
	rint i, j;
	long own=0;
	int cell;
	int mul = 10;
	if (dir == 0) // UP direction
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][0][i];  //Col varies
			own = own*mul + cell ;
			printf("own is %d, mul is %d\n", own, mul);

		}
	}
	
	else if (dir == 1)
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][i][BSIZE-1];  
			own = own * mul + cell;
			printf("own is %d, mul is %d\n",own,mul);
		}
	}
	else if (dir == 2)
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][BSIZE-1][BSIZE-i-1];  
			own = own * mul + cell;
		}
	}
	else
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][BSIZE - i -1][0];  //Col varies
			own = own * mul + cell;
		}

	}
	return own;
}
long GetNeigh(int id, int dir)
{
	rint i, j;
	long own = 0;
	int cell;
	int mul = 10;
	if (dir == 0) // UP direction
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][0][i];  //Col varies
			own = own * mul + cell;
			printf("own is %d, mul is %d\n", own, mul);

		}
	}

	else if (dir == 1)
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][i][BSIZE - 1];
			own = own * mul + cell;
			printf("own is %d, mul is %d\n", own, mul);
		}
	}
	else if (dir == 2)
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][BSIZE - 1][BSIZE - i - 1];
			own = own * mul + cell;
		}
	}
	else
	{
		for (i = 0;i < BSIZE;i++)
		{
			cell = db[id][BSIZE - i - 1][0];  //Col varies
			own = own * mul + cell;
		}

	}
	return own;
}
int main()
{

	printf("Matrix Rotation....\n");
	int n;
	int i;
	freopen("input.txt", "r", stdin);
	scanf("%d",&n);
	int j, k;
	char str[10];
	printf("Num of Blocks %d\n",n);
	for(i=0;i<n;i++)
	{
		printf("Block-1 %d \n",i);
		for (j = 0;j < 4;j++)
		{
			scanf("%s",str);
			for (k = 0;k < 4;k++)
			{	
				db[i][j][k] = str[k]-'0';
				printf("%d",db[i][j][k]);
			}

			//update the block information
			for (int l = 0;l < 4;l++)
			{
				printf("Direction os %d\n",l);
				blk[i][l].ownseq = GetOwn(i,l);
				printf("Get own is %d\n", blk[i][l].ownseq);
//				blk[i][l].nseq = GetNeigh(i, l);
	//			blk[i][l].ownid = i;

				_getch();

			}
			printf("\n");
		}
	}

	
	_getch();
	return 0;
}