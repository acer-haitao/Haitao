/*************************************************************************
  > File Name: test.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Sat 02 Jul 2016 02:22:54 PM CST
 ************************************************************************/

#include <stdio.h>


int fun()
{
    int count = 10;
	/*如果不加static每调用一次 重新赋值 
	 * 加上之后再次调用直接取上一次的值(在静态常量存储只初始化一次)*/
	return count--;
}
int count = 1;
int main(int argc, char *argv[])
{
	extern char a;
	printf("%c \n",a);
	msg();
	printf("--------------分割线--------------\n");
	printf("global\t\tlocal static\n");

	for (; count < 10; count++)
	{
		printf("%d\t\t%d\n",count, fun());

	}

	return 0;
}
