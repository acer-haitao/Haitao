/*************************************************************************
  > File Name: 1.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Thu 04 Aug 2016 01:11:58 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int n_to_n(int x, char *str, int n)
{
	int i = 0, j = 0;
	int tmp;
	if (n < 10)
	{
		while(x > 0)
		{
			str[i++] = x % n + '0';
			x = x / n;
		}
	} 
	else
	{
		while(x > 0)
		{
			tmp = x % n;
			if (tmp < 10)
			{
				str[i] = tmp + '0';
			}
			else
			{
				str[i] = tmp - 10  + 'A';
			}
			i++;
			x = x / n;
		}
	}

	i--;
	for (j = 0 ; j < i; j++, i--)
	{
		char t;
		t = str[i];
		str[i] = str[j];
		str[j] = t;
	}

	return 0;
}
int main(int argc, char *argv[])
{
	int x = 106;
	int n = 16;
	char str[81] = {'\0'};

	n_to_n(x, str, n);
	printf("%s\n",str);
	return 0;
}
