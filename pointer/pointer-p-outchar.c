/*************************************************************************
    > File Name: pointer-p-outchar.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 02:10:19 PM CST
 ************************************************************************/

#include <stdio.h>
int main(int argc, char *argv[])
{
	char *string[] = {"zhaoxxx", "lixxx", "wangxxx"};
	/* 指针数组，每一个数组元素相当于一个指针变量*/
	char **p;
	/* 1 *(*p)--*p定义一个指针变量，在前加*代表p是指向一个指针变量。	
	*  2 *p表示p所指向的另一个指针变量，一个地址; **p是p间接指向的对象的值
	*/
	int i;
	p = string;/* 指针指向字符串首地址  */
	for (i = 0; i < 3; i++)
	{
		printf("%s\n",*(p + i));
	}
	
	return 0;
}
