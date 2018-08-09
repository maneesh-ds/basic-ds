#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <conio.h>

// input : 0x1234  output :  0x11223344
int encoded(int a)
{
	int i = 0;
	int mask = 0x0f;
	int t = 0;
	int out = 0;
	int j = 0;
	for (i = 0;i < 4;i++)
	{
		t = (a >> (4 * i)) & mask;
		out = out | (t << j);
		j = j + 4;
		out = out | (t << j);
		j = j + 4;

	}
	return out;
}
//inout : 0x11223344 , Output : 0x1234
//Here Interger range : 2 Bytes only
int decode(int out)
{
	int in = 0;
	int i, j=0;
	int mask = 0x0f;
	int a1, a2;
	int a=0;
	for (i = 0;i < 4;i++)
	{
		// Extract the 1 nibble (input = ox1234 , output :  0x4)
		a1 = (out >> 4 * j++) & mask;
		a2 = (out >> 4 * j++) & mask;

		a = a1 & a2;
		in = in | a << (4*i);
		//printf("a1=0x%x, a2=0x%x,in=0x%x\n",a1,a2,in);
	}
	return in;
}
//Input Range : 4 Bytes
int Extract_Byte(int input)
{
	printf("Extracr the Byte : 0x%x\n",input);
	int i = 0;
	int mask = 0xff;
	int a=0;
	for (i = 0;i < 4;i++)
	{
		a = (input >> 8 * i) & mask;
		printf("num is 0x%x\n",a);
	}
	return 0;
}

//Input Range : 4 Bytes
int Extract_nibble(int input)
{
	printf("Extracr the nibble : 0x%x\n", input);
	int i = 0;
	int mask = 0x0f;
	int a = 0;
	for (i = 0;i < 8;i++)
	{
		a = (input >> 4 * i) & mask;
		printf("num is 0x%x\n", a);
	}
	return 0;
}
//Input Range : 32 bit
// dec to bin convertor
int Extract_bit(int input)
{
	printf("Extracr the bit : 0x%x\n", input);
	int i = 0;
	int mask = 0x01;
	int a = 0;
	for (i = 0;i < 32;i++)
	{
		a = (input >>  i) & mask;
		printf("bit is 0x%x\n", a);
	}
	return 0;
}


//input : 0x55 , Output after flip: 0x51 after flip 2 bit
void Get_Flip(int n,int loc)
{
	int a = 0;
	a = n ^ (1 << loc);
	printf("Number after flip 0X%x\n",a);
}

//input : 0x55 , Output after flip: 0x57 after set 1 bit
void Set_bit(int n, int loc)
{
	int a = 0;
	a = n | (1 << loc);
	printf("Number after set 0X%x\n", a);
}
int main()
{
	int a = 0x1234;
	int out=encoded(a);
	printf("0X%x\n",out);
	//Decode the number and generate the same
	int in = decode(out);
	printf("0X%x\n", in);
	if(a == in)
		printf("Encoded-Decoded working fine\n");

	int num = 0x12345678;
	Extract_Byte(num);
	Extract_nibble(num);

	num = 20;
	Extract_bit(num);
	Get_Flip(0x55, 2);
	Set_bit(0x55, 1);
	_getch();
	return 0;
}