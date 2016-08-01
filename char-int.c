/*************************************************************************
    > File Name: char-int.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 05 Jul 2016 05:54:44 PM CST
 ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
	int num;
	int i = 0;
	int j = 0;

	char buf[128] = {0};
	char buf1[128] = {0};

	puts("请输入整数");
	scanf("%d",&num);
	
	while(num)
	{
		buf[i++] = num % 10 + 48;
		num = num / 10;
		printf("i = %d\n", i);
	}
	buf[i] = '\0';
	for (j = 0; j < i; j++)
	{
		buf1[j] = buf[i - j - 1];
		printf("j = %d\n",j);
	}
	buf1[j] = '\0';

	printf("%s\n",buf1);
	return 0;
}
