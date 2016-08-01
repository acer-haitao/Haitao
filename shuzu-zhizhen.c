/*************************************************************************
    > File Name: shuzu-zhizhen.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 06 Jul 2016 07:04:25 PM CST
 ************************************************************************/

#include <stdio.h>

#if 1
void fun(char **p)
{
	*p +=2;
}
int main(int argc, char *argv[])
{
	char *a[] = {"123", "abc", "456"};
	char **p = a;
	fun(p);
	printf("%s\n",*p);
	return 0;
}
#endif

