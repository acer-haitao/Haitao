/*************************************************************************
    > File Name: shuzuout.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 11:46:05 AM CST
 ************************************************************************/

#include <stdio.h>
int main(int argc, char *argv[])
{
	int a[10];
	int *p, i;

	for (i = 0; i < 10; i++)
	{
		a[i] = i;
	}
	for (p = a; p < (a + 10); p++)
	{
		printf("%d\t", *p);
	}
	putchar(10);
	return 0;
}
