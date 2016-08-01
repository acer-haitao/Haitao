/*************************************************************************
    > File Name: huiwenchar.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 04 Jul 2016 04:44:48 PM CST
 ************************************************************************/

#include <stdio.h>

int palind(char str[], int k, int i)
{
	if (str[k] == str[i - k] && k == 0) /* 递归结束条件  */
	{
		return 1;
	}
	else if (str[k] == str[i - k]) 	/* 判断相对应的两个字符是否相等  */
	{
		palind(str, k-1, i);
	}
	else 

	return 0;
}
int main(int argc, char *argv[])
{
	int i = 0, n = 0;
	char ch, str[20];
	while((ch = getchar()) != '\n')
	{
		str[i] = ch;
		i++;
	}
	if (i % 2 == 0)
	{
		n = palind(str, (i/2), i - 1);
	}
	else
	{
		n = palind(str, (i/2 - 1), i - 1);
	}
	if (n == 0)
	{
		printf("不是回文\n");
	}
	else
		printf("是回文\n");
	return 0;
}
