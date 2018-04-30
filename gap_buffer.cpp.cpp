//Gap Buffer implementation
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>


int bufstart;
int bufend;
int gapstart;
int gavend;
int cursor;


#define MAX_SIZE 20

//global string

char gapbuffer[20];


void init_index()
{
	bufstart = 0;
	bufend = (MAX_SIZE/2) - 1;

	gapstart = MAX_SIZE-1;
	gavend = MAX_SIZE-1;
	cursor = 0;

	

}

void CopyData(char *str,int len)
{
	int i = 0;

	for (i = 0;i < len;i++)
	{

		gapbuffer[bufstart + i] = str[i];

	}

}

void DisplayData()
{
	int i = 0;

	printf("Text Data is \n");
	for (i = 0;i < MAX_SIZE;i++)
	{
		if (gapbuffer[i] != 0)
			printf("%c",gapbuffer[i]);

	}

	printf("\n");
}

int m_strlen(char *str)
{
	int len = 0;
	int i = 0;
	for (i = 0;str[i];i++)
		len++;

	return len;
}


void InsertData(char *str)
{

	int offset = 0;
	int i = 0;
	printf("buffer start %d, cursor %d\n",bufstart, cursor);

	int len = m_strlen(str);

	if (cursor == bufstart)
	{
		printf("No shift or copy required...copy directly\n");
		CopyData(str,len);
		bufstart = bufstart + len;
		cursor = cursor + len;
	}
	else if (cursor == (bufend + 1))
	{
		printf("no more space left in Text Editor\n");
			
	}
	else if (cursor < bufstart)
	{
		printf("Data needs to insert in b/w, so move the data in Gap Buffer\n");
		//calulate the index
		offset = bufstart - cursor;
		printf("offset is %d\n",offset);

		//copy the data from buffer to Gap buffer (cursor to bufstart), size =  offset

		//Calulate the gapstart based on offset 

		gapstart = gapstart - offset;

		for (i = 0;i < offset;i++)
		{
			gapbuffer[gapstart + i] = gapbuffer[cursor + i];
		}

		//Insert the opriginal data now
		for (i = 0;i < len;i++)
		{
			gapbuffer[cursor + i] = str[i];
		}
		//update the cursor location

		cursor = cursor + len;
		bufstart = bufstart + len - offset;

		printf("updated cursor=%d,bufstart=%d\n",cursor,bufstart);
		
	
	}
	else if (cursor > bufstart)
	{
		printf("it means.. data needs to insert in Gap Buffer directly\n");
		
	}
}

int main()
{

	printf("Gap Buffer, max length of string is 10 \n");
	
	init_index();
	int opr = 0;
	char str[MAX_SIZE];

	freopen("input.txt","r",stdin);
	
	
	while (1) {
		scanf("%d", &opr);
		


		printf("operation is %d\n", opr);
		switch (opr)
		{

			case 1:
			{
				scanf("%s", str);

				printf("insert : at last cursor position\n");
				InsertData(str);
				break;
			}


			case 2:
			{
				printf("select the string from t1 to t2 location\n");
				break;
			}

			case 3:
			{
				printf("cut the string : t1 to t2\n");
				break;
			}

			case 4:
			{
				printf("copy the string at given position\n");
				break;
			}

			case 5:
			{
				printf("Paste the string at given position\n");
				break;
			}
			case 6:
			{
				printf("Remove\n");
				break;
			}
			case 7:
			{
				printf("Set the cursor location");
				int c;
				scanf("%d", &c);
				cursor = c;
				printf("current cursor location :%d\n", cursor);

				break;

			}
			case 8:
			{
				printf("Display current data in Text Editor\n");
				DisplayData();
				break;
			}
			case 0:
			{
				printf("exit\n");
				_getch();
				return 0;
			}
		}
	}
	_getch();
	return 0;

}