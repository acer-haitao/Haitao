/*************************************************************************
    > File Name: count111.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 29 Jun 2016 07:33:08 PM PDT
 ************************************************************************/

#include <stdio.h>

int fun(unsigned int a)
{
	int count = 0;
	while(a)
	{
#if 0		
		a = a & (a -1);
		printf("a = %x\n",a);
		count++;
#endif
		count += 0x1 & a;
		a = a >> 1;
	}
	return count;

int main(int argc, char *argv[])
{
	unsigned int a;
	printf("请输入整数\n");
	scanf("%d",&a);
	printf("%d \n", fun(a));
	return 0;
}
