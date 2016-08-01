/*************************************************************************
    > File Name: spacefirstlast.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 22 Jul 2016 02:11:03 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getnum(char *str, char *buf, int *len)
{
	char *mystr = str;
	char *mybuf = buf;
	int i = 0;
	int j = strlen(mystr) - 1;

	if (mystr == NULL || mybuf == NULL)
	{
		return -1;
	}
#if 1
	while(isspace(*(mystr+i)) && (*(mystr + i) != '\0')) i++;
	while(isspace(*(mystr+j)) && (*(mystr + j) != '\0')) j--;
	
	printf("-----------------------\n");
	printf("j = %d i = %d\n", j, i);
	*len = j - i + 1;
	strncpy(mybuf, mystr + i, *len);
	*(mybuf + *len) = '\0';
	return 0;
#endif
#if 0
	while(*mystr++)
	{
		if (*mystr == ' ')
		{
			continue;
		}
		else
		{
			*mybuf = *mystr;
			mybuf++;
		}
	}

	return 0;
#endif
}

int main(int argc, char *argv[])
{
	char *str = "\nabcdadfghag   ";
	char buf[128] = {0};
	int len = 0;
	int ret;

	ret = getnum(str, buf, &len);
	if (ret < 0 )
	{
		printf("errro\n");
		return ret;
	}
	printf("%s--->%d\n",buf,len);
	return 0;


}
int main02(int argc, char *argv[])
{
	char *src = "helloworld";
	char *dest = NULL;

	int len = strlen(src) - 1;
	dest = (char *)malloc(len);
	char *d = dest;
	char *s = &src[len];
	printf("len = %d\n", len);
	while(len-- != -1)
	{
		*d++ = *s--;
	}
	printf("%s\n",dest);
	return 0;
}
