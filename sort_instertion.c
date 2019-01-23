//Program : Insertion sort : To sort the given list and get 5 min items from list
// One condition : In case same numbers, sort the list based on ID
//Input :   Num :  10, 20, 12 , 20, 10, 6 , 10 , 2
//           ID :  2,  3 , 1 , 4, 5, 9 , 7 , 8
// it seems good in case run time numbers are keep coming
// Avg Case complexity : O(nlogn) 
// Worst Case :  O(n2)
// Better algo : Heap Sort for such similar problem

#include <stdio.h>
#include <conio.h>

#define S 10

int N=0;
int idcount=0;
int ip[S][2];

int list[S][2];


void insertion_sort(int n)
{
	int i,j;
	int num;
	int id;
	for(i=0;i<n;i++)
	{
		if(i==0)	
		{
			list[i][0]=ip[i][0];
			list[i][1]=ip[i][1];
			continue;		
		}	

		for(j=i;j>=0;j--)
		{
			if(ip[i][0]	> list[j-1][0])
			{
				list[j][0]=ip[i][0];
				list[j][1]=ip[i][1];

				break;
			}
			else if (ip[i][0] < list[j-1][0])
			{
				//swap it
				int num = list[j-1][0];
				id = list[j-1][1];

				list[j-1][0]=ip[i][0];
				list[j-1][1]=ip[i][1];

				list[j][0]=num;
				list[j][1]=id;
			}
			else 
			{
				
				//add the num in list and check for id case
				list[j][0]=ip[i][0];
				list[j][1]=ip[i][1];
		
				//Now we need to check for ID case			
				if(ip[i][1] < list[j-1][1])
				{
					//printf("#..swap it \n");
					//swap it with previous entry in list
					int id1 = list[j-1][1];
					list[j-1][1] = ip[i][1];
					list[j][1]=id1; 
				}
				else
					break;
				
			}

		}
	}
	
	
}
int main()
{
	freopen("input.txt","r",stdin);
	int i;

	//first time add N numbers 
	scanf("%d",&N);
	for(i=0;i<N;i++)
		scanf("%d",&ip[i][0]);	
	
	for(i=0;i<N;i++) {
	
		scanf("%d",&ip[i][1]);	
		printf("%d ",ip[i][1]);
	}	
	//Insertion alog
	
	insertion_sort(N);
	
	for(i=0;i<N;i++)
	{
		printf("Num %d ->Id %d\n",list[i][0],list[i][1]);
	}
	return 0;

	_getch();
}

