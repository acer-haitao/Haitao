/*************************************************************************
    > File Name: min-max.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 01:46:50 PM CST
 ************************************************************************/

#include <stdio.h>
int max_min(int *p, int len, int *max, int *min)
{
	int *q;
	*max = *min = *p;
	printf("*p = %d\n", *p);
	for (q = p + 1; q < p + len; q++)
	{
		if (*q > *max)
		{
			*max = *q;
		}
		else if (*q < *min)
		{
			*min = *q;
		}
	}		
	return 0;
}
int main(int argc, char *argv[])
{
	int i, a[10] ={1,2,3,22,11,31,32,5,44,223};
	int min, max;
	max_min(a, 10, &max, &min);
	printf("max = %d\n", max);
	printf("min = %d\n", min);
	return 0;
}
