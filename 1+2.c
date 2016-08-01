/*************************************************************************
    > File Name: 1+2.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 27 Jul 2016 12:08:05 PM CST
 ************************************************************************/

#include <stdio.h>

float get_sum(int n)
{
	int i;
	float sum = 0;
	float s;
	for (i = 1; i <= n; i++)
	{
		sum += i;
		s += 1/sum;
		printf("%f\n",s);
	}
	return s;
}
int main(int argc, char *argv[])
{
	float sum = 0;
	sum = get_sum(11);
	printf("%f\n", sum);
	return 0;
}
