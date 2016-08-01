/*************************************************************************
    > File Name: 1.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 21 Jun 2016 04:33:21 AM PDT
 ************************************************************************/

#include <stdio.h>
unsigned int sum(unsigned int base);
int main(int argc, char *argv[])
{
	int a = 0x01020304;
	char *p;
	p = &a;
	printf("a = %d\n",*p);
	printf("sum = %d\n", sum(1));
	return 0;
}
unsigned int sum(unsigned int base)
{
	static unsigned int sum = 0;
	unsigned int index;
	for(index = 1; index <= base; index++)
	{
		sum += index;
	}
	return sum;
}
