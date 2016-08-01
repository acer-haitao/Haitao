/*************************************************************************
    > File Name: paixu.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 11:06:30 AM CST
 ************************************************************************/

#include <stdio.h>

int swap(int *p, int *q)
{
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
	return 0;
}

int fun_order (int *q1, int *q2, int *q3)
{
	/* 选择排序的思想a>b a>c b>c  */
	if (*q1 > *q2)
	{
		swap(q1, q2);
	}
	if(*q1 > *q3)
	{
		swap(q1, q3);
	}
	if (*q2 > *q3)
	{
		swap(q2, q3);
	}
	return 0;
}
int main(int argc, char *argv[])
{
	int a, b, c;
	int *q1, *q2, *q3;

	printf("请输入三个整形数据以逗号隔开:\n");
	scanf("%d,%d,%d", &a, &b, &c);

	q1 = &a;
	q2 = &b;
	q3 = &c;
	/* 指针作为形參 */
	fun_order(q1, q2, q3);
	printf("%d, %d, %d \n", a, b, c);
	return 0;
}
