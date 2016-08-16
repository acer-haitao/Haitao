/*************************************************************************
    > File Name: 11.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 04 Aug 2016 02:46:26 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_m(char **p, int num)
{
	*p = (char *)malloc(num);
}

int main01(int argc, char *argv[])
{
	char *str = NULL;
	int num = 100;
	get_m(&str,100);
	strcpy(str,"hell");
	printf("%s\n",str);
	return 0;
}

int sort(int n, int base)
{
	if (n == 0)
	{
		return 0;
	}
	sort(n/base, base);
	printf("%d", n%base);
}
int main(int argc, char *argv[])
{
	int tmp = 0;
	int base = 0;
	puts("请输入整数：");
	scanf("%d", &tmp);
	getchar();
	puts("请输入转换的进制：");
	scanf("%d", &base);

	sort(tmp, base);
	putchar(10);
}
