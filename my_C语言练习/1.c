/*************************************************************************
    > File Name: 1.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 05 Jul 2016 04:31:51 PM CST
 ************************************************************************/

#include <stdio.h>
struct node{
	short a;
	char b;
	float c;
}sc;

int main(int argc, char *argv[])
{
char ch[] = {"abc\0def"};
	char *p = ch;
	int a = 0;
	int i=((a=2*3,a|0x11),(a*5,a&0x1));
	printf("%c\n", *p + 4);
	printf("%d + %d\n",sizeof(sc), 7 >> 1);
	printf("sizeof(0xAABBCCDDU)=%d\n",sizeof(0xAABBCCDDU));

	printf("--------------分割线--------------\n");
	printf("i = %d\n",i);
	return 0;
}
