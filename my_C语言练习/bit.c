/*************************************************************************
    > File Name: bit.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 05 Jul 2016 06:45:23 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
typedef struct node{
	int a:2;
	int b:2;
	int c:1;
}test;/* a表示node的低两位，b表示node的3-4位 c表示node的第5位 */
/***********************************************************************
 * *个位域必须存储在同一个字节中，不能跨两个字节
 * int a:2
 * int b:4
 * int c:3
 * ab占6个字节，c占3个字节，这样一个完整的字节就没法存储a b和c, c就得
 * 跨两个字节，这是不允许的，当一个字节所剩空间不够存另外一位域，因该
 * 从下一单元起存放该位域。
 ***********************************************************************/ 
int i = 5;
int main(int argc, char *argv[])
{
	test t;
	t.a = 1;
	t.b = 3;
	t.c = 1;
	int i ;
	printf("i = %d\n", i);
	printf("-------------bit位域--------------\n");
	printf("%d\n", t.a);
	printf("%d\n", t.b);
	printf("%d\n" ,t.c);
	printf("--------------sizeof--------------\n");
	char s[] = "hello world!";
	char *p = s;
	int n = 10;
	printf("sizeof(s)=%d sizeof(p)= %d strlen(p)= %d sizeof(n) = %d\n", sizeof(s), sizeof(p),strlen(p),sizeof(n));
	printf("--------------分割线--------------\n");
	return 0;
}
