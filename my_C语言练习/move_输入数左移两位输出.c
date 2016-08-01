/*************************************************************************
    > File Name: move_输入数左移两位输出.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 01 Aug 2016 06:55:26 PM CST
 ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
	int a;
	printf("请输入整数：");
	scanf("%d", &a);
	a = a << 2;
	printf("%d\n",a);
	return 0;
}
