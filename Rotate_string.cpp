//Rotate String :  apple (org word)
//  pleap : After Roate 
// If we roate above word 2 times, we can recover orginal word.
//in this program , check if given test word can be recovers and if yes... how many times need be rotate


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>


#define MODULAS  256

//Magic Numbers
int h = 1;
int d = 31;

int pattern_hash = 0;

int GenerateHash(char *str)
{

	int i;
	int hashv = 0;
	for (i = 0;str[i];i++)
	{
		hashv = (hashv * d + str[i]) % MODULAS;
	}
	//printf("hash is %d\n",hashv);
	return hashv;
}

int GenerateRollingHash(char *str, int size)
{

	int i = 0;
	int hashv = 0;
	int old_hash = 0;
	int move_count = 0;
	int new_hash = 0;

	old_hash = GenerateHash(str);

	if (old_hash == pattern_hash) {

		printf("String found :No Rotation in given string\n");
		return 0;
	}

	while (move_count < size)
	{
		printf("old hash %d, rotate char is %c , move count %d \n",old_hash,str[move_count],move_count);

		new_hash = d * (old_hash - (h * str[move_count]));
		new_hash = (new_hash + str[move_count]) % MODULAS;
	
		if (new_hash < 0)
			new_hash = new_hash + MODULAS;

		old_hash = new_hash;
		move_count++;

		if(new_hash == pattern_hash)
		{
			printf("String is match : num of rotation is %d\n",move_count);
			return move_count;
		}
	}
	return  -1;
}

void Init(int n)
{
	int i = 0;

	// Here loop count : n = size -1
	//if size of pattern 3, then count loop is 3 -1 = 2 due to polynominal 
	//h is very important value for this approch, need to memorize
	for (i = 0;i < n-1;i++)
	{
		h = (h * d) % MODULAS;
	}

}

int main()
{

	//Calulate the H value
	
	char ipstr[15];
	char opstr[15];
	int size = 0;
	int res = 0;

	freopen("input.txt", "r", stdin);

	scanf("%s",ipstr);
	scanf("%s",opstr);
	scanf("%d",&size);

	Init(size);


	printf("ipstr=%s, opstr=%s, size=%d\n",ipstr,opstr,size);
	//Geneate the hash for Input String
	pattern_hash = GenerateHash(ipstr);

	printf("Input Pattern Hash %d\n",pattern_hash);
	res = GenerateRollingHash(opstr,size);
	
	if (res == -1)
		printf("String can not be match\n");
	_getch();
	return 0;
}