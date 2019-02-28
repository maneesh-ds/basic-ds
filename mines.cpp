#include <stdio.h>
#include <conio.h>

#define rint register int
#define uchar int 
#define lint long long int
#define S 201 

uchar x[S][S];

uchar t3[S][S];
uchar t5[S][S];
uchar t7[S][S];


int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};


void init()
{
	rint i,j;
	for(i=0;i<S;i++)
	{
		for(j=0;j<S;j++)
		{
			t3[i][j]=1;
			t5[i][j]=1;
			t7[i][j]=1;
			x[i][j] =0;
		}	
	}	
}

void display(int r, int c, uchar t[S][S])
{
	printf("Display %d %d\n",r,c);
	rint i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%d ",t[i][j]);
		}
		printf("\n");	
	}	
	
	_getch();
}
lint GetHash(int x, int y,uchar h[S][S], int type)
{
	lint hash = 5381;
	rint i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			if(type == 1)
				hash = hash*31 + 1;
			else
				hash = hash*31 + h[i][j];
			
		}
	}	
	return hash;
}

void GetColideMine(int r, int c, uchar xt[S][S],uchar t[S][S])
{
	
	printf("## Get Colide Mine %d %d\n",r,c);

	rint i,j;
	int v;
	rint k=0;
	int x1;
	int y1;

	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{

			v = xt[i][j];
			if(v == 1)	
			{
				
				t[i][j]=0;
				//set 0 to all neighbour
				for(k=0;k<4;k++)	
				{
					x1 = i + dx[k];
					y1 = j + dy[k];
					
					if(x1 < 0 || x1 > r || y1 < 0 || y1 > c)
						continue;
					else
					{
						//printf("##{%d %d}\n",x1,y1);
						t[x1][y1]=0;
					}
				}
			}
		}
		
	//	_getch();
	}
}



lint GetMines(int r, int c, int T)
{
	lint res;
	printf("T %d\n",T);
	int diff =0;
	
	if((T%2) == 0)	
	{
		printf("EVEN Time... Get the direct Hash\n");
	//	res =GetHash(r,c,x,1);
		return res;
	}
	else if( T == 0 || T == 1)
	{
		printf("Get the Hash of Input\n");
	//	res = Gethash(r,c,x,0);	
		return res;		
	}
	
	else if ( T < 6)
	{
		if(T == 3)
		{	
			GetColideMine(r,c,x,t3);
			display(r,c,t3);
		//	res = Gethash(r,c,t3,0);
		}
		else if ( T == 5)
		{
			GetColideMine(r,c,x,t3);
			GetColideMine(r,c,t3,t5);
			//res = Gethash(r,c,t5,0);
		}
		return res;
	}	
	else
	{
		GetColideMine(r,c,x,t3);
		display(r,c,t3);

		GetColideMine(r,c,t3,t5);
		display(r,c,t5);

		GetColideMine(r,c,t5,t7);
		display(r,c,t7);
	
		//check if t7 is equal to t5 for confirmation
		//	diff= GetCompare(t3,t7);	
		//	printf("Compare result is %d\n",diff);
		
		//3 7 11 15
		//5 9 13 17
		if(T % 4 == 1)
		{
			printf("#1 : Series : 5 9 13 ---17\n");
			//		res = Gethash(r,c,t5,0);
		}
		else
		{
			printf("#2 : Series : 3 7 11 ---15\n");
			//		res = Gethash(r,c,t3,0);
		}
		return res;	
	}
}
int main()
{
	
	int tc;
	int r,c;
	int T;
	
	rint i,j; 
	rint l;
	
	lint res=0;
	freopen("input.txt","r",stdin);
	
	scanf("%d",&tc);
	for(l=1;l<=tc;l++)
	{
		
		init();
		scanf("%d%d%d",&r,&c,&T);		
		printf("%d %d %d\n",r,c,T);
		
		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)
			{
				scanf("%d",&x[i][j]);				
			}
		}		
		
		res = GetMines(r,c,T);	
		printf("#%d %ld\n",tc,res);

	}
	
_getch();
	return 0;	
}





