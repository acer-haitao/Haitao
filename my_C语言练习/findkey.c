/*************************************************************************
    > File Name: findkey.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 22 Jul 2016 04:33:59 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>


int getkey(char *keyvalue, char *key, char *mybuf, int *len)
{
	char *p = NULL;

	if (keyvalue == NULL || key == NULL || mybuf == NULL)
	{
		return -1;
	}

	if ((p = strstr(keyvalue, key)) == NULL)
	{
		return -1;
	}
	p = p + strlen(key);

	if (*p == '=')
	{
		p = strstr(p, "=");
		p = p + strlen("=");
	}
	trmspace(p, mybuf, len);
	return 0;
}

int trmspace(char *str, char *mybuf, int *len)
{
	int mylen = 0;
	while(*str++)
	{
		if (*str == ' ')
		{
			continue;
		}
		else
		{
			*mybuf = *str;
			mybuf++;
			mylen++;
		}
	}
	*len = mylen - 1;
	return 0;
}

int main(int argc, char *argv[])
{
	char *keyvalue = "key2=    abcdef     ";
	char *key = "key2";
	char buf[1024] = {0};
	int ret, len;

	ret = getkey(keyvalue,/*in*/ key,/*in*/ buf, /*out*/ &len);
	if (ret < 0)
	{
		printf("return -1;\n");
		return ret;
	}

	printf("mybuf--%s--len=%d\n",buf, len);
	return 0;
}
