/*************************************************************************
    > File Name: char_copy.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 02 Jul 2016 10:57:09 AM CST
 ************************************************************************/

#include <stdio.h>
int main(int argc, char *argv[])
{
	char buf1[] = "abcdefg";
	char buf2[128]; 

	char *from = buf1;
	char *to = buf2;
	
	while(*to++= *from++);	
	printf("to = %s\n", buf2);
	return 0;
}
