/*************************************************************************
    > File Name: yuv422_rgb.c
    > Author:张明志
    > Mail:862207403@qq.com 
    > Created Time: Sat 17 Sep 2016 01:32:50 AM EDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
static void yuv422_rgb24(unsigned char *yuv422,unsigned char *rgb24,int width,int height)
{
	int x,y;
	uint8_t *yuv444;
#if 0 
	if((yuv444 = malloc(width*height*3))==NULL)
	{
        printf("fail to malloc\n");
	}
#endif 

	if((yuv444 = (uint8_t *)malloc(width*height*3))==NULL)
	{
        printf("fail to malloc\n");
	}
	printf("%p\n",yuv444);
	x=0;
	y=0;
	while(x<10)
	{
//		yuv444[y] = yuv422[x];
		printf("%d",yuv422[x]);
#if 0
		yuv444[y+1]=yuv422[x+1];
		yuv444[y+2]=yuv422[x+3];
		yuv444[y+3]=yuv422[x+2];
		yuv444[y+4]=yuv422[x+1];
		yuv444[y+5]=yuv422[x+3];
#endif
		x=x+4;
		y=y+6;
		printf("%d,%d\n",x,y);
	}
	free(yuv444);
}



int main(int argc, const char *argv[])
{
	//yuyv_to_rgb("3.yuyv","rgb24");
    yuv422_rgb24("3.yuyv","3.rgb",640,480);
	return 0;
}
