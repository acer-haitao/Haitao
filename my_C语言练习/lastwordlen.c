/*************************************************************************
    > File Name: lastwordlen.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 07 Jul 2016 07:17:08 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *str = "hello worldabcd";
	int len = strlen(str);
	int i, num;

	for (i = len - 1; i >= 0; i--)
	{
		if (*(str + i) != ' ')
		{
			printf("len = %d, world = %c\n", len, *(str + i));
			num++;
		}
		else
			break;
	}
	printf("num = %d\n", num);
	
	return 0;
}
