
//Rolling Hash with 2-D data
#include <stdio.h>
#include <conio.h>



#define P 1007
#define rint register int
#define uint unsigned int

#define S 2001
uint power;

uint rowhash[S];

uint txt[S][S];
uint pattern[S];

//Get Hash for Pattern and as well for old hash value in text data
unsigned int GetHash(uint str[S], int n)
{
	rint i;
	unsigned int hash=0;

	for(i=0;i<n;i++)	
		hash = hash*P + str[i]; // P Prime Number 

	return hash;	
}
unsigned int p_row=1;
unsigned int p_col=1;


void init()
{
	p_row=1;
	p_col=1;
	
}


int main()
{
	
	printf("Pattern Matching ....\n");	
	unsigned int phash =0;
	rint i,j;
	
	uint final_hash=0;
	
	int T;
	int tc;
	int fcount=0;
	int Px,Py,Tx,Ty;
	char str[S];
	uint final_old_hash = 0;

	int plen=0;
	freopen("input.txt","r",stdin);
	
	scanf("%d",&T);
	
	for(tc=0;tc<T;tc++)
	{
		fcount=0;
		scanf("%d%d%d%d",&Px,&Py,&Tx,&Ty);
		
		//Calculate the Hash for Pattern
		unsigned int pat_hash=0;
		unsigned int hash=0;

		for(i=0;i<Px;i++)
		{
			scanf("%s",str);
			hash=0;
			for(j=0;j<Py;j++)
			{
				if(str[j] == 'o')
					hash = hash*P ; // P Prime Number 
				else
					hash = hash*P + 1; // P Prime Number 
			}
			//printf("#hash is %d\n",rowhash[i]);
			pat_hash = pat_hash*P + hash; // P Prime Number 
		}
		
		//Hash value of Pattern
		printf("Hash value of Pattern %d\n ",pat_hash);					
		
		
		//Start with Text Data	
		for(i=0;i<Tx;i++)
		{
			scanf("%s",str);
			for(j=0;j<Ty;j++)
			{
				if(str[j] == 'o')
					txt[i][j]=0;
				else
					txt[i][j]=1;
			}
		}
		
		//Now apply the Rolling Hash
		printf("Pattern Len : for Row %d\n",Px);		
		
		//Polynominal Power for Row
		for(i=0;i<Py;i++)
			p_row = p_row*P;
			
		//Polynominal Power for Coloum
		for(i=0;i<Px;i++)
			p_col = p_col*P;
		
		uint first_row_hash=0;
		//for all text Rows, till Py (Size Of Pattern)
		k=0;
		
		while(k < Ty)
		{
		
			for(i=0;i<Tx;i++)
			{
				rowhash[i]=0;
				
				for(j=k;j<Py;j++)
					rowhash[i] = rowhash[i]*P + txt[i][j];
					
			}
			
			
			
			//Calculate the Hash coloum wise and complare the result with Pattern hash
			//first hash calulate
			final_old_hash = 0;
			for(i=0;i<Px;i++) //Patten Size : Px : Row Size
				final_old_hash = final_old_hash*P + rowhash[i];
			
			for(i=Px;i<Tx;i++)	
			{
				final_old_hash = final_old_hash*P + rowhash[i] - rowhash[i-Px]*pow_row;
				//Compare this value from the Patten hash
				if(final_old_hash == pat_hash)
				{
					printf("Pattern seems match\n");
					fcount++;
				}
		  }
			
			//Increase the coloum by one
			k=Py;
		}
		
		
		
		
		init(Px);
		uint block_hash=0;
		
		

		//Get the Hash from First Block
		for(i=0;i<Px;i++)
		{
			hash = 0;
			for(j=0;j<Py;j++)		
			{
				hash = hash*P + txt[i][j];
			}
			rowhash[i]=hash;			
			block_hash = block_hash*P + rowhash[i];
		}		
		
		//check if first block hash match
		if(block_hash == pat_hash)
		{
			printf("Match found : Compare the 2D matrix one by one\n");
			fcount++;
		}
		
		//Pattern lengh 
		plen = py;
		//Now apply the Rolling Hash concept
		//Calculate the block wise ..pick row wise
		for(j)
		for(i=0;j<Px;i++)
		{
			newhash = rowhash[i]*P + txt[i][plen];
		
		}
		
		
	}	
	return 0;
}

