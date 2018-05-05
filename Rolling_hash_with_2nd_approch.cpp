


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>


#define MODULAS  1007

int pattern_hash = 0;

//Important to remind the concept of h
int h = 1;
//Magic Number for Hash Calulation
int d = 31;


int GetHash(char str[], int count)
{
	int i = 0;
	int hash = 0;
	for (i = 0;i<count;i++)
	{
		hash = (hash * d + str[i]) % MODULAS;
	}

	printf("hash is %d\n", hash);
	return hash;
}

int GenerateHashAndCheck(char str[], int n)
{
	int old_hash = 0;
	int new_hash = 0;
	int  i = 0;

	old_hash= GetHash(str, n);

	for (i = n;str[i];i++)
	{

		new_hash = d * old_hash - (h * str[i - n]));
		new_hash = new_hash % MODULAS;	
		new_hash = new_hash + str[i];
		new_hash = new_hash % MODULAS;

		if (new_hash < 0)
			new_hash = new_hash + MODULAS;

		printf("new hash is %d\n",new_hash);

		old_hash = new_hash;

		if (pattern_hash == new_hash)
		{
			printf("string found\n");
			return 1;
		}

	}
	
	return 0;
}
int main()
{

	char str[] = "djsahdjhlasnkdjasdssjdhjasdwertyuiopasdfghjkjdlaksasdfghjklzxcvbnmqwertyuiopasdsadsadsadsadasdadasdaqweqwdqweasdfghjklzxcvbnmqwertyuiqwqwww";
	char find[] = "asdfghjklzxcvbnmqwertyuioy";
	

	int search_pattern_len = 26;
	int res = 0;
	int i;

	// The value of h would be "pow(d, M-1)%q : Polynominal Hash concept"
	//Quite important to remind this
	//Kindly for every different pattern length, need to recalulate the hash for Test String as well
	// Can not be use the same Hash value 

	for (i = 0; i < search_pattern_len; i++)
	{
		h = (h * d) % MODULAS;
	}
	//Calulate the Hash value of Search Pattern
	pattern_hash = GetHash(find, search_pattern_len);
	res = GenerateHashAndCheck(str, search_pattern_len);
	
	if (res)
		printf("Pattern found\n");
	else
		printf("Pattern not found\n");
	_getch();

	return 0;
}
