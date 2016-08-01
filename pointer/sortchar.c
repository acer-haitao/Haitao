/*************************************************************************
    > File Name: pointer-p-outchar.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 02:10:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
int sort(char **p, int len)
{
	char *tmp;
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			if (strcmp(*(p + i), *(p + j)) > 0)
			{
				tmp = *(p + i);
				*(p + i) = *(p + j);
				*(p + j) = tmp;
			}
		}
		
	}
	return 0;
}
int main(int argc, char *argv[])
{
	char *string[] = {"zhaoxxx", "lixxx", "wangxxx", "abcd", "bcdadfa", "hghg"};
	/* 指针数组，每一个数组元素相当于一个指针变量*/
	char **p;
	/* 1 *(*p)--*p定义一个指针变量，在前加*代表p是指向一个指针变量。	
	*  2 *p表示p所指向的另一个指针变量，一个地址; **p是p间接指向的对象的值
	*/
	int i;
	p = string;/* 指针指向字符串首地址  */
	printf("指针数组的大小：%d\n",sizeof(string)/sizeof(int));
	for (i = 0; i < sizeof(string)/sizeof(int); i++)
	{
		printf("%s\n",*(p + i));
	}
	sort(p, 6);
	printf("--------------分割线--------------\n");
	for (i = 0; i < 6; i++)
	{
		printf("%s\n",*(p + i));
	}
	return 0;
}
