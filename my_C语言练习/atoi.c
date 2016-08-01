/*************************************************************************
  > File Name: atoi.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Wed 29 Jun 2016 01:09:09 AM PDT
 ************************************************************************/

#include <stdio.h>
int atoi(const char *str)
{
	int sum = 0;

	while(*str != '\0')
	{
		sum = 10 * sum + *str++ - '0';	
	}
	printf("%d\n", sum);
	return 0;
}
int main(int argc, char *argv[])
{
	char buf[64];
	printf("请输入数字字符串:\n");
	scanf("%s",buf);
	atoi(buf);
	return 0;
}
