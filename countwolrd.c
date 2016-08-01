/*************************************************************************
    > File Name: 1.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 22 Jun 2016 03:02:55 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 128
int main(int argc, char *argv[])
{
	FILE *fp;
		

	fp = fopen(argv[1], "r");
	if(fp < 0)
	{
		printf("打开失败\n");
		return -1;
	}

	char ch;
/*******************************************/
	*
 		* *******************************************/
	int num = 0;
	int word;
	while((ch = fgetc(fp) )!= EOF)
	{
		if(ch == ' ') word = 0;
		else if(word == 0)
		{
			word = 1;
			num++;
		}
	}
	printf("%d\n", num - 1);
	return 0;
}
