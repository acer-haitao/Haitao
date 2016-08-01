/*************************************************************************
    > File Name: maopao.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 28 Jun 2016 04:15:11 AM PDT
 ************************************************************************/
/*  */
#include <stdio.h>
int main(int argc, char *argv[])
{
	int buf[] = {1,4,100,43,5,6,12,16};
	int i = 0, j = 0;
	int tmp;
	for (i = 0; i < 8; i++)
	{		
		printf("排序前：%d  ",buf[i]);
	}

	for (i = 0; i < 8 - 1; i++) /* 比较n-1次而不是n次 */
	{
		for (j = i; j < 8 - i -1; j++)/* 比较n-i-1次 */
		{
			if (buf[j] > buf[j + 1])
			{
				tmp = buf[j];
				buf[j] = buf[j + 1];
				buf[j + 1] = tmp;
			}
		}
	}
	putchar(10);
	for (i = 0; i < 8; i++)
	{		
		printf("排序后：%d   ",buf[i]);
	}
	
	return 0;
	
}
