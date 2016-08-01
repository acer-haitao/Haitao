/*************************************************************************
    > File Name: stackresver.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 20 Jul 2016 09:43:36 AM CST
 ************************************************************************/

#include <stdio.h>

int stackresver(char *p)
{
	if (NULL == p)
	{
		return -1;
	}
	if (*p == '\0')
	{
		return 0;
	}
	stackresver(p + 1);
	printf("%c\n",*p);
}
int main(int argc, char *argv[])
{
	char str[] = "abcdef";
	char *p = str;
	stackresver(p);
	return 0;
}
