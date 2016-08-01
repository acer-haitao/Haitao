/*************************************************************************
    > File Name: 指针比较三个数.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 24 Mar 2016 07:17:49 AM PDT
 ************************************************************************/

#include<stdio.h>

int swap();
int exchange();

int main(int argc, const char *argv[])
{	
	int a,b,c;
	printf("请输入三个数:");
	scanf("%d%d%d",&a,&b,&c);
	int *p=&a;
	int *q=&b;
	int *l=&c;
	exchange(p,q,l);
	printf("%d  %d  %d\n",a,b,c);
	return 0;
}
int swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
} 
int exchange(int *p,int *q,int *l)
{
	if(*p > *q)
	{
		swap(p,q);
	}
	if(*p > *l)
	{
	swap(p,l);

	}
	if(*q > *l)
	{
		swap(q,l);

	}
}
