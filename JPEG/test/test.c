/*************************************************************************
    > File Name: test.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 19 Sep 2016 05:42:05 AM PDT
 ************************************************************************/
#include <stdio.h>
#include "converter.h"

int main(int argc, char *argv[])
{
	
	yuyv422_to_rgb("/home/linux/JPEG/test/3.yuyv", "3.rgb", 128, 256);

	return 0;
}
