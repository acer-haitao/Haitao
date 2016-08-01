/*************************************************************************
    > File Name: strcpy.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 29 Jun 2016 01:40:48 AM PDT
 ************************************************************************/

#include <stdio.h>
int main(int argc, char *argv[])
{
	char s1[200],s2[100];
	int i = 0;

	puts("请输入字符串s1:");
	gets(s1);
	while(s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	printf("s2 = %s\n",s2);
	return 0;
}
