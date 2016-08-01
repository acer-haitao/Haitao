/*************************************************************************
  > File Name: jishufenkai.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Wed 29 Jun 2016 05:47:23 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#if 0
int main(int argc, char *argv[])
{
	int buf[] = {1, 3 ,2, 8, 9, 32, 7};
	int buf1[20];
	int i;
	for (i = 0; i < sizeof(buf)/sizeof(int); i++)
	{
		if (buf[i]%2 != 0)
		{
			printf("%d  ",buf[i]);
		}
	}
	puts("\n");
	puts("------华丽的分割线--------\n");
	for(i = 0; i < sizeof(buf)/sizeof(int); i++)
	{
		if (buf[i]%2 == 0)
		{
			printf("%d  ",buf[i]);
		}
	}
	puts("\n");
	return 0;
}
#endif
#if 0
int main(int argc, char *argv[])
{
	int buf[] = {1, 3 ,2, 8, 9, 32, 7};
	int buf1[20];
	int i, j, k;
	for (i = 0, j = 0; i < sizeof(buf)/sizeof(int); i++)
	{
		if (buf[i]%2 != 0)
		{
			buf1[j] = buf[i];
			j++;
		}
	}
	for(i = 0, k =j; i < sizeof(buf)/sizeof(int); i++)
	{
		if (buf[i]%2 == 0)
		{
			buf1[k] = buf[i];
			k++;
		}
	}
	for(i = 0; i <sizeof(buf)/sizeof(int); i++)
	{
		printf("%d  ",buf1[i]);
	}

	printf("\n--------------分割线--------------\n");
	return 0;
}
#endif
int fun1(int *data, int len)
{
	if (data == NULL || len == 0)
	{
		printf("没有数据\n");
		return -1;
	}
	int *first = data;
	int *last = data + len - 1;
	int tmp = 0;
	/***********************************************************************
	 *    指针指向第一个和最后一个，往中间移，相遇之前，如果第一个指向偶数
	 *第二个指向奇数则交换
	 ***********************************************************************/ 
	while(first < last)
	{
		/* 判断是否为奇数，如果为奇数则指针往后移动，直到遇到偶数退出循环进入下一个while  */
		while(first < last && (*first & 0x1) != 0) first++;
		/* 判断是否为偶数，如果为偶数则指针往前移,直到遇到奇数退出循环进入if */
		while(first < last && (*last & 0x1) == 0)  last--;

		if (first < last)
		{
			tmp = *first;
			*first = *last;
			*last = tmp;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int buf[] = {1,3,2,5,22,31,76,33,8};
	int len = sizeof(buf)/sizeof(int);
	int i = 0;

	fun1(buf, len);

	for (i = 0; i < len; i++)
	{
		printf("%d  ", buf[i]);
	}
	
	return 0;
}
