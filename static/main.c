/*************************************************************************
    > File Name: main.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 02 Jul 2016 02:22:54 PM CST
 ************************************************************************/

#include <stdio.h>
/* 定义的全局变量a 和msg函数没有加static关键字，
 * 同时编译多文件时全局可见，加之后被隐藏*/
char a = 'A'; 
void msg()
{
	printf("hello world\n");
}
