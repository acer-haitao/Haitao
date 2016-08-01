/*************************************************************************
    > File Name: test.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 27 Jul 2016 03:29:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void merge(char *d, int size, char *s1, char *s2)
{
	while(*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 < *s2)
		{
			*d++  = *s1++;
		}
		else
		{
			*d++ = *s2++;
		}
	}
	while(*s1 != '\0') *d++ = *s1++;
	while(*s2 != '\0') *d++ = *s2++;
	*d = 0;
}
int main(int argc, char *argv[])
{
	char s1[] = "acmghn";
	char s2[] = "bcfhi";
	char s3[20];
	memset(s3, 0, sizeof(s3));
	merge(s3, sizeof(s3) - 1, s1, s2);
	puts(s3);
	return 0;
}
