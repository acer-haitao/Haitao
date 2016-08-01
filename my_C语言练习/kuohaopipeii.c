/*************************************************************************
    > File Name: kuohaopipeii.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 27 Jul 2016 10:23:12 AM CST
 ************************************************************************/

#include <stdio.h>
#define  false  0
#define  true   1
/*括号匹配*/
int  is_match(char *str)
{
	char *tmp = str;

	if (tmp == NULL)
	{
		printf("NULL\n");
		return false;
	}
#if 0
	int len1 = 0, len2 = 0, len3 = 0, len4 = 0;
	int len11 = 0, len22 = 0, len33 = 0, len44 = 0, flag = 0;
	int i = 0;
	for(i = 0; tmp[i] != '\0'; i++)
	{
		if (tmp[i] == '(')
		{
			len1++;
		}
		if(len1 > len11)/* 记录左括号个数*/
		{
			len11 = len1;
		}
	    if (len1 == 0 && tmp[i] == ')')
		{
			flag = 1;
			break;
		}
		if (len1 > 0 && tmp[i] == ')')
		{
			len1--;
		}
	}
	if (len1 > 0 || flag == 1)
	{
		printf("不匹配len1 = %d, len11 = %d\n",len1, len11);
	}
	else 
	{
		printf("len1 = %d len11 = %d\n", len1, len11);
	}

#endif
	int i = 0;
	int flag = 1;

	while(tmp[i] != '\0' && flag == 1)
	{
		switch(tmp[i])
		{
			case '(':
			case ']':
			case '{':
			case '>': 
				/* 入栈*/
				break;
			case ')':
				/* 出栈*/
				break;
			case ']':
				break;
			case '}':
				break;
			case '>':
				break;
		}
		i++;
	}
}

int main(int argc, char *argv[])
{
	char *buf = "((1+2)))";
	is_match(buf);
	return 0;
}
