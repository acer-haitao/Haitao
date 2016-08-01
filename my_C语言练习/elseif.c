/*************************************************************************
    > File Name: elseif.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sun 31 Jul 2016 01:16:38 PM CST
 ************************************************************************/

#include <stdio.h>

int main01(int argc, char *argv[])
{	
	
	int n = 200;
	int num = 0;

	if (n > 500)
	{
		num = 1;
	}
	else if (n > 300)
	{
		num = 2;
	}
	else if (n > 200)
	{
		num = 3;
	}
	else if (n > 100)
	{
		num = 4;
	}
	else
	{
		num = 5;
	}

	printf("num =%d\n", num);
	return 0;
}
int main(int argc, char *argv[])
{
	int n = 500;
	int num = 0;

	if (n > 500)
	{
		num = 1;
	}
    if (n > 300)
	{
		num = 2;
	}
    if (n > 200)
	{
		num = 3;
	}
	else if (n > 100)
	{
		num = 4;
	}
	else
	{
		num = 5;
	}

	printf("num =%d\n", num);
	return 0;

	return 0;
}
