/*************************************************************************
    > File Name: 10的阶乘.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 24 Mar 2016 06:35:47 AM PDT
 ************************************************************************/

#include<stdio.h>
int main(int argc, const char *argv[])
{
	float n =10;
	float t=1;
	int i = 1; 
	if(n == 0 || n ==1)
	{
		printf("n = %f\n",n);
	}
	while(i <= n)
	{
		t = t * i ;
		i++;
	}
	printf("t = %f\n",t);
	
	return 0;
}
