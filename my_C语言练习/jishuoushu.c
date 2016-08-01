/*************************************************************************
  > File Name: jishuoushu.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Mon 01 Aug 2016 06:33:59 PM CST
 ************************************************************************/

#include <stdio.h>



#define N 10



void sort(int *a, int n);

int main()

{

	int a[N] = {1,2,3,4,5,6,7,8,9,10};

	int i, j;

	sort(a, N);

	for(i = 0; i < N; i++)

	{

		printf("%d ", a[i]);

	}

	puts("");

	return 0;

}

void sort(int *a, int n)

{

	int i,len,temp;

	len=n-1;

	for(i=0;i<len;)

	{

		if((a[i]%2)==0) //判断是否为偶数

		{

			a[len] ^= a[i];

			a[i] ^= a[len];

			a[len] ^= a[i];

			len--;

		}

		else

			i++;

	}

	return;

}


