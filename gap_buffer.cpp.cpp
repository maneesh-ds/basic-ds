//Gap Buffer implementation
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>


int bufstart;
int bufend;
int gapstart;
int gapend;
int cursor;


int gM1 = 0;
int gM2 = 0;

#define MAX_SIZE 50

//global string

char gapbuffer[20];


void init_index()
{
	bufstart = 0;
	bufend = (MAX_SIZE/2) - 1;

	gapstart = MAX_SIZE-1;
	gapend = MAX_SIZE-1;
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
	for (i = 0;i < bufstart;i++)
	{
		printf("%c",gapbuffer[i]);

	}
	printf("\n Data in right gap buffer\n");
	for (i = gapstart;i < gapend;i++)
	{
		printf("%c", gapbuffer[i]);
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

void CursorMove()
{
	printf("Custor Move \n");
	int i = 0;
	int offset;

	if (cursor < bufstart)
	{
		//		printf("Data needs to insert in b/w, so move the data in Gap Buffer\n");
		//calulate the index
		offset = bufstart - cursor;
		printf("offset is %d\n", offset);

		//copy the data from buffer to Gap buffer (cursor to bufstart), size =  offset
		//Calulate the gapstart based on offset 
		gapstart = gapstart - offset;
		for (i = 0;i < offset;i++)
		{
			gapbuffer[gapstart + i] = gapbuffer[cursor + i];
		}

		bufstart = bufstart - offset;
		//	printf("updated cursor=%d,bufstart=%d\n", cursor, bufstart);
	}

	else if (cursor > bufstart)
	{

		printf("data is in right side\n");
		offset = cursor - bufstart;

		//move the data from left portion to right portion
		for (i = 0;i < offset;i++)
		{
			gapbuffer[bufstart + i] = gapbuffer[gapstart + i];
		}
		gapstart = gapstart + offset;
		bufstart = bufstart + offset;
	}
}

void SelectData()
{
	//three possible cases
	//1. m1 and m2 available in left side only
	//2. m1 and m2 available in right side only
	//3. m1 and m2 lie b/w left and right
	//m1 - m2compare with bufstart
	// m1- m2 compare with gapstart and gap end
	//keep the g 

	//Just calculate the index
	 //abcd | efs
	//update the cursor position
	int offset;
	int copyoffset = 0;
	int total_char_in_gap = 0;
	int  i = 0;
	int m1;
	int m2;
	if (gM1 >=bufstart)
	{
		printf("select is in right side gapstart %d, gapend %d\n",gapstart,gapend);
		offset = gM2 - gM1 + 1;
		
		m1 = gM1 + MAX_SIZE / 2;
		m2 = gM2 + MAX_SIZE / 2;

		copyoffset = gM1 - gapstart;

		for (i = 0;i < copyoffset;i++)
		{
			gapbuffer[gapend - gM2 - copyoffset + i] = gapbuffer[gapstart + i];
		}
		cursor = gM1;
		gapstart = gM1 - offset;
		printf("updated gapstart is  %d, cursor is %d\n", gapstart, cursor);
		CursorMove();

	}
	else if (gM2 <= bufstart)
	{
		
		offset = gM2 - gM1 + 1;
		copyoffset = bufstart - gM2 - 1;
		cursor = gM1;

		for (i = 0;i < copyoffset;i++)
		{
			gapbuffer[gM1 + i] = gapbuffer[bufstart-copyoffset+i];
		}

		bufstart = gM1 + copyoffset;
		printf("updated bufstart is  %d, cursor is %d\n",bufstart,cursor);
		CursorMove();
	}
	else
	{
		printf("select lie in between of left and right\n");
	}


}

void InsertData(char *str)
{

	int offset = 0;
	int i = 0;
	printf("buffer start %d, cursor %d\n",bufstart, cursor);

	//check if if text was selected
	if (gM1 != 0 || gM2 != 0)
	{
		printf("Somewhere data was selected\n");
		cursor = gM2;
		SelectData();

	}

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
}



int main()
{

	//printf("Gap Buffer, max length of string is 10 \n");
	
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
				int m1, m2;
				scanf("%d %d",&m1,&m2);
				printf("select the string from m1=%d to m2=%d location\n",m1,m2);
				gM1 = m1;
				gM2 = m2;
				
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
				CursorMove();
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
