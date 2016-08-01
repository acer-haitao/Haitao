/*************************************************************************
    > File Name: strstr-dowhile.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 22 Jul 2016 03:29:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int getnum(char *str, int *count)
{
	char *tmp = str;
	int num = 0;

	if (tmp == NULL)
	{
		printf("NULL\n");
		return -1;
	}
#if 0
	do
	{
		tmp = strstr(tmp, "abcd");
		if (tmp != NULL)
		{
			num++;
			tmp = tmp + strlen("abcd");
		}
		else
		{
			break;
		}
	}while(*tmp != '\0');
	
	*count = num;
#endif
	while(tmp = strstr(tmp, "abcd"))
	{
		num++;
		tmp = tmp + strlen("abcd");
		if (*tmp == '\0')
		{
			break;
		}
	}

	*count = num;
	return 0;
}

int main(int argc, char *argv[])
{
	char str[] = "abcd1234acdgahgjkaabcd";
	int count = 0;
	int ret;

	ret = getnum(str, &count);
	if (ret < 0)
	{
		printf("return\n");
	}
	printf("count = %d\n", count);
	return 0;
}
