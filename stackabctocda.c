/*************************************************************************
    > File Name: stackabctocda.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 22 Jul 2016 03:49:34 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

/***********************************************************************
 *						递归实现字符串逆序 
 ************************************************************************/ 
int inverse(char *str, char *mybuf)
{
	if(*str == '\0')
	{
		return -1;
	}

	inverse(str + 1, mybuf);
	printf("%c\n",*str);
	strncat(mybuf, str, 1);
	return 0;
}

int main(int argc, char *argv[])
{
	char str[] = "abcdeeghi";
	char mybuf[128] = {0};
	int ret;

	ret = inverse(str, mybuf);
	if (ret < 0)
	{
		printf("NULL\n");
		return ret;
	}

	printf("mybuf-->%s\n", mybuf);
	return 0;
}
