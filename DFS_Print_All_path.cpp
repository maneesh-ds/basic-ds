//To print all possible path from source to destination (inlcuding only given specific nodes)
//However, this is not ensure the shortest path

/* : Input
4 4
2 0 1 1
1 1 0 0
0 1 1 3
1 1 1 1
2 3
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>

int a[4][4];

int dx[4] = {0,1,0,-1}; 
int dy[4] = {1,0,-1,0};

int visited[4][4];

void init()
{
	int i, j;

	for (i = 0;i < 4;i++)
		for (j = 0;j < 4;j++)
			visited[i][j] = -1;
}

int valid(int x, int y)
{
	if (x < 0 || x > 3 || y < 0 || y > 3)
		return 0;

	if (visited[x][y] != -1)
		return 0;

	if (a[x][y] == 0)
		return 0;

	return 1;
}
int path[4][4];

void init_path()
{
	int i, j;
	for (i = 0;i < 4;i++)
	{
		for (j=0;j < 4;j++)
		{
			path[i][j] = 0;
		}
	}
}

//To get all the path from the source to destinaton
//kind of backtrack
int flag = 0;
void DFS(int x, int y,int d[2])
{
	int x1, y1;
	int i, j;
	int res = 0;
	printf("x =%d, y=%d\n",x,y);
	path[x][y] = 1;

	//Just example: to check if (3,2) is in desired path
	if (x == 3 && y == 2)
		flag = 1;
	
	if (d[0] == x && d[1] == y )
	{
		printf("Found the Path..\n");
		if (flag == 0)
			printf("not desired path\n");
		else
		{
			int cost = 0;
			//let's print the path
			for (i = 0;i < 4;i++)
			{
				for (j = 0;j < 4;j++)
				{
					if (path[i][j] == 1)
					{
						cost++;
						printf("Path is {%d %d}\n", i, j);
					}
				}
			}
			printf("Total distance is %d\n", cost);
			flag = 0;
		}
		return;

	}
	
	for (i = 0;i < 4;i++)
	{
	
		x1 = dx[i] + x;
		y1 = dy[i] + y;
		//printf("x1 =%d, y1=%d\n", x1, y1);

		res = valid(x1,y1);

		if (res)
		{
			visited[x1][y1] = 1;
			DFS(x1,y1,d);
			visited[x1][y1] = -1;
			path[x1][y1] = 0;
		}
	}
	
	//backtrack for other path
}

//Using BFS... print all path



int main()
{
	printf("Print all path\n");
	int x, y;
	int i, j;
	int d[2];
	freopen("input.txt", "r", stdin);
	scanf("%d %d",&x,&y);
	
	for (i = 0;i < x;i++)
	{
		for (j = 0;j < y;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}

	scanf("%d %d",&d[0],&d[1]);
	//apply the DFS to get the path
	
	init();
	init_path();
	DFS(0, 0,d);

	_getch();


}