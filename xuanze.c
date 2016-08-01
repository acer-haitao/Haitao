/*************************************************************************
    > File Name: xuanze.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 28 Jun 2016 04:54:27 AM PDT
 ************************************************************************/

#include <stdio.h>
int main(int argc, char *argv[])
{
	int buf[] = {1,4,100,43,5,6,12,16};
	int i = 0, j = 0;
	int tmp;
	int k;
	for (i = 0; i < 8 -1; i++)
	{
		k = i;
		for (j = i + 1; j < 8; j++)/* j < 8而不是小于××-i buf[k]-->一直比到buf[7]  */
		{
			if (buf[k] > buf[j])
			{
				tmp = buf[j];
				buf[j] = buf[k];
				buf[k] =tmp;
			}
		}	
	}
	
	for (i = 0; i < 8; i++)
	{
		printf("%d  ",buf[i]);
	}
	
	return 0;
}
