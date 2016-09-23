#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jpeglib.h"

 

#define image_width1 640
#define image_height1 480

JSAMPLE * image_buffer;
typedef unsigned char uint8_t;



void write_RGB_JPEG_file (char * filename,unsigned char* yuvData, int quality,int width,int height)
{
	image_buffer=yuvData;

		struct jpeg_compress_struct cinfo;

		struct jpeg_error_mgr jerr;     

		FILE * outfile; /* target file */
		JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
		int row_stride; /* physical row width in image buffer */

		cinfo.err = jpeg_std_error(&jerr);

		jpeg_create_compress(&cinfo);


		if ((outfile = fopen(filename, "wb")) == NULL) {
				fprintf(stderr, "can't open %s\n", filename);
				exit(1);
		}
		jpeg_stdio_dest(&cinfo, outfile);


		cinfo.image_width = width; /* image width and height, in pixels */
		cinfo.image_height =height;
		cinfo.input_components = 3; /* # of color components per pixel */
		cinfo.in_color_space = JCS_RGB; /* colorspace of input image */

		jpeg_set_defaults(&cinfo);

		jpeg_set_quality(&cinfo, quality, TRUE );

		jpeg_start_compress(&cinfo, TRUE);

        row_stride=640*3;

		while( cinfo.next_scanline < cinfo.image_height)
		{   
			row_pointer[0] =  &image_buffer[cinfo.next_scanline * row_stride];
			jpeg_write_scanlines(&cinfo, row_pointer, 1);
		}
		jpeg_finish_compress(&cinfo);
		fclose(outfile);
		jpeg_destroy_compress(&cinfo);
}



static void yuv422_rgb24(unsigned char *yuv422,unsigned char *rgb24,int width,int height)
{
	int x,y;
	uint8_t *yuv444;
	if((yuv444 = malloc(width*height*3))==NULL)
	{
        printf("fail to malloc\n");
	}
	x=0;
	y=0;
	while(x<width*height*2)
	{
		yuv444[y]=yuv422[x];
		yuv444[y+1]=yuv422[x+1];
		yuv444[y+2]=yuv422[x+3];
		yuv444[y+3]=yuv422[x+2];
		yuv444[y+4]=yuv422[x+1];
		yuv444[y+5]=yuv422[x+3];
		x=x+4;
		y=y+6;
	}
	for(x=0;x<=width*height*3;x+=3)
	{
		rgb24[x+2]=yuv444[x]+1.402*(yuv444[x+2]-128);
		rgb24[x+1]=yuv444[x]-0.34414*(yuv444[x+1]-128)-0.71414*(yuv444[x+2]-128);
		rgb24[x]=yuv444[x]+1.772*(yuv444[x+1]-128);
		if(rgb24[x]>255)
			rgb24[x]=255;
		if (rgb24[x]<0)
			rgb24[x]=0;
		if(rgb24[x+1]>255)
			rgb24[x+1]=255;
		if(rgb24[x+1]<0)
			rgb24[x+1]=0;
		if(rgb24[x+2]>255)
			rgb24[x+2]=255;
		if(rgb24[x+2]<0)
			rgb24[x+2]=0;
	}
	free(yuv444);
}


int main(int argc, const char *argv[])
{
	FILE *fp_y;
	FILE *fp_r;
	unsigned char buff_y[640*480*2];//裝yuyv圖片的数据的數組
	unsigned char buff_r[640*480*3];//装rgb图片的数据的数组

	fp_y=fopen("test.yuv","rb");//打开yuyv格式的图片
	fread(buff_y,1,sizeof(buff_y),fp_y);//把yuyv格式的图片数据读到buff_y数组中
    yuv422_rgb24(buff_y,buff_r,image_width1,image_height1);

    write_RGB_JPEG_file ("3.jpeg",buff_r ,80,image_width1 ,image_height1);
	return 0;
}


