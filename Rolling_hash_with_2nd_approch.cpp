
//Rolling Hash with 1-D data
#include <stdio.h>
#include <conio.h>

char pat[4]= "def";


#define P 1007
#define rint register int
#define uint unsigned int

uint power;

//Get Hash for Pattern and as well for old hash value in text data
unsigned int GetHash(char *str, int n)
{
	rint i;
	unsigned int hash=0;

	for(i=0;i<n;i++)	
		hash = hash*P + str[i]; // P Prime Number 

	return hash;	
}


void init(int n)
{
	//Get the Power value : it is changed if pattern length change
	//only required during hash generation from text
	rint i=0;
	unsigned int pw=1;
	for(i=0;i<n;i++)
		pw = pw*P;
	power = pw;		

}
int main()
{
	
	printf("Pattern Matching ....\n");	
	unsigned int phash =0;
	int i=0;
	int plen =3;
	char txt[10] = "abcghidef";
	
	
	init(plen);


	//Get the Hash value for Pattern
	printf("Pattern String %s\n",pat);
	phash = GetHash(pat,plen);
	
	unsigned int Oldhash=0;
	Oldhash = GetHash(txt,plen);
	printf("Old Hash is %d\n",Oldhash);
	
	//Sliding window Concept : For Rolling Hash Calculation
	for(i=plen;txt[i];i++)
	{
		Oldhash = Oldhash*P + txt[i] - (txt[i-plen] *power); //power: Polinoimial of Prime Number								

		printf("#Hash is %d\n",Oldhash);

		if(Oldhash == phash)
			printf("Pattern found\n"
	}
	_getch();
	return 0;
}

