/*************************************************************************
    > File Name: yuv422_yuv420p.c
    > Author:张明志
    > Mail:862207403@qq.com 
    > Created Time: Sat 17 Sep 2016 03:44:23 AM EDT
 ************************************************************************/

#include <stdio.h>
int yuv422toyuv420p(unsigned char *out,const unsigned char *in,unsigned int width,unsigned int height)
{
	unsigned char *y=out;
	unsigned char *u =out + width*height;
	unsigned char *v = out + width*height+width*height/4;


	unsigned int i,j;
	unsigned int base_h;
	unsigned int is_y =1,is_u=1;
unsigned int y_index =0,u_index =0,v_index=0;

	unsigned long yuv422_length =2*width*height;


	for(i=0;i<yuv422_length;i+=2)//把Ｙ提取出来
	{
	//	*(y+y_index)=*(in+i);
		y_index++;
	}
	for(i=0;i<height;i+=2)//把偶数行丢弃了
	{
		base_h =i*width*2;
		for(j=base_h+1;j<base_h+width*2;j+=2)
		{
			if(is_u)
			{
				*(u+u_index)=*(in+j);
				u_index++;
				is_u=0;
			}
			else 
			{
				*(v+v_index)=*(in+j);
				v_index++;
				is_u=1;
			}
		}
	}
	return 1;
}
int main(int argc, const char *argv[])
{
	
 yuv422toyuv420p("yuv420p","3.yuyv",640,480);
	return 0;
}
