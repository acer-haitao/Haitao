/*************************************************************************
    > File Name: fgets.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 21 Jul 2016 05:55:43 PM CST
 ************************************************************************/

#include <stdio.h>
int main(int argc, char *argv[])
{
//	char buf[128];
//	scanf("%s",buf);
	//fgets(buf, 128, stdin);
//	printf("%s\n",buf);
    char buf[128];
	while(scanf("%s",buf)!=EOF)
	{
		printf("%s",buf);
		putchar(' ');
	}
	putchar(10);
	printf("end main");
	return 0;
}
