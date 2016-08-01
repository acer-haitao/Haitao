/*************************************************************************
    > File Name: reser_二进制特定位翻转.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 01 Aug 2016 06:48:13 PM CST
 ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("请输入整数:");
	unsigned int result;
	int a, b;

	scanf("%d", &a);
	b = 15;
	result = b^a;
	printf("%d\n",result);

	return 0;
}
