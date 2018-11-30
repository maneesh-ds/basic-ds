
Conversation opened. 1 read message.

Skip to content
Using Gmail with screen readers
hea 

heap

Maneesh Jain <maneeshjain1982@gmail.com>
Attachments
Mon, Sep 10, 9:00 PM
to maneesh.jain



-- 
Regards,
Maneesh Jain


	I’m protected online with Avast Free Antivirus. Get it here — it’s free forever.
Attachments area

//Heap Implemenation : Max Heap and Min Heap

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>


int max_heap[10000];
int min_heap[10000];

int minsize = 0;
int maxsize = 0;


void init()
{
	max_heap[0] = 0;
	min_heap[0] = 0;
	minsize = 0;
	maxsize = 0;

}

int parent(int i)
{
	return ((i - 1) / 2);
}
int left(int i)
{
	return (2 * i + 1);
}
int right(int i)
{
	return (2 * i + 2);
}

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void max_insert(int d)
{

	int i = maxsize;
	max_heap[maxsize] = d;
	
	while (i != 0 && (max_heap[i] > max_heap[parent(i)]))
	{
		swap(&max_heap[i],&max_heap[parent(i)]);
		i = parent(i);
	}
	maxsize++;

}

void min_insert(int d)
{
	int i = minsize;
	min_heap[minsize] = d;

	while (i != 0 && (min_heap[i] < min_heap[parent(i)]))
	{
		swap(&min_heap[i], &min_heap[parent(i)]);
		i = parent(i);
	}
	minsize++;


}

void min_heapify(int i)
{
	int largest;

	int l = left(i);
	int r = right(i);
	largest = i;

	if (l < minsize && (min_heap[l] < min_heap[largest]))
	{
		largest = l;
	}

	if (r < minsize && (min_heap[r] < min_heap[largest]))
	{
		largest = r;
	}

	if (largest != i)
	{
		swap(&min_heap[i], &min_heap[largest]);
		min_heapify(largest);
	}

}
void max_heapify(int i)
{
	int largest;

	int l = left(i);
	int r = right(i);
	largest = i;

	if (l < maxsize && (max_heap[l] > max_heap[largest]))
	{
		largest = l;
	}

	if (r < maxsize && (max_heap[r] > max_heap[largest]))
	{
		largest = r;
	}

	if (largest != i)
	{
		swap(&max_heap[i], &max_heap[largest]);
		//i = largest;
		max_heapify(largest);
	}
}

int max_extract()
{
	int res = 0;

	if (maxsize == 0)
		return -1;

	else if (maxsize==1)
	{
		res = max_heap[0];
		maxsize--;
    }
	else
	{
		res = max_heap[0];
		max_heap[0] = max_heap[maxsize-1];
		maxsize--;
	
		max_heapify(0);
	}
	return res;
}

int min_extract()
{
	int res = 0;

	if (minsize == 0)
		return -1;

	else if (minsize == 1)
	{
		res = min_heap[0];
		minsize--;
	}
	else
	{
		res = min_heap[0];
		min_heap[0] = min_heap[minsize-1];
		minsize--;
		min_heapify(0);
	}
	return res;
}

void max_display()
{

	int i = 0;
	for (i = 0;i < maxsize;i++)
	{
		printf("%d \n",max_heap[i]);
	}
}
void min_display()
{

	int i = 0;
	for (i = 0;i < minsize;i++)
	{
		printf("%d \n", min_heap[i]);
	}
}

void AdjustHeaps()
{
	int d1 = maxsize - minsize;
	int max = 1;
	int res;

	if (d1 < 0)
	{
		d1 = -1 * d1;
		max = 0;
	}
	if (d1 > 1)
	{
		if (max == 1)
		{
			res = max_extract();
			min_insert(res);
		}
		else
		{
			res = min_extract();
			max_insert(res);
		}
	}
}
void insert_num(int num)
{
	if (minsize == 0)
	{
		min_insert(num);
		return;
	}

	if (num > min_heap[0])
		min_insert(num);
	else
		max_insert(num);
	AdjustHeaps();
}

float  Getmid()
{
	float res = 0;	
	int max, min;
	if ((maxsize + minsize) % 2 == 0)
	{
		max = max_heap[0];
		min = min_heap[0];
		res = float(max + min) / 2;
	}
	else
	{
		if (( maxsize - minsize) < 0)
			res = min_heap[0];
		else
			res = max_heap[0];

	}
	return res;
}

int main()
{
	printf("Heap based system\n");
	float res;
	int i;
	int ret;
	int N;
	int d;
	freopen("input.txt","r",stdin);
	scanf("%d", &N);
	for (i = 0;i < N;i++)
	{
		scanf("%d",&d);
		insert_num(d);
		res = Getmid();
		printf("Mid is %0.1f\n", res);

	}
	_getch();
}


source_heap_based_sorting.cpp
Displaying source_heap_based_sorting.cpp.
