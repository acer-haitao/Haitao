/*************************************************************************
  > File Name: test.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Wed 14 Sep 2016 09:15:18 PM CST
 ************************************************************************/


#include <stdio.h>
#include "jpeglib.h"

#if 1
int main(int argc, char *argv[])
{
	//yuv420sp_to_jpg("/home/linux/JPEG/jpeg/3.jpg", 1024, 768, "/home/linux/JPEG/jpeg/3.yuv");
	write_YUV_JPEG_file("/home/linux/JPEG/jpeg/abc.jpg","/home/linux/JPEG/jpeg/3.yuv",1024,768,24);
	return 0;
}
#endif
