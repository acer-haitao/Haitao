#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jpeglib.h"
#if 1
void write_YUV_JPEG_file (char * filename, unsigned char* yuvData, int quality,
		int image_width,int image_height)
{

	struct jpeg_compress_struct cinfo;

	struct jpeg_error_mgr jerr;

	FILE * outfile; /* target file */
	//JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
	//int row_stride; /* physical row width in image buffer */
	JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
	int row_stride; /* physical row width in image buffer */

	JSAMPIMAGE buffer;

	int band,i,buf_width[3],buf_height[3];
	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_compress(&cinfo);


	if ((outfile = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(1);
	}
	jpeg_stdio_dest(&cinfo, outfile);


	cinfo.image_width = image_width; /* image width and height, in pixels */
	cinfo.image_height = image_height;
	cinfo.input_components = 3; /* # of color components per pixel */
	cinfo.in_color_space = JCS_YCbCr; /* colorspace of input image */

	jpeg_set_defaults(&cinfo);

	jpeg_set_quality(&cinfo, quality, TRUE );

	//////////////////////////////
	cinfo.raw_data_in = TRUE;
	cinfo.jpeg_color_space = JCS_YCbCr;
	cinfo.comp_info[0].h_samp_factor = 2;
	cinfo.comp_info[0].v_samp_factor = 2;
	/////////////////////////

	jpeg_start_compress(&cinfo, TRUE);

	buffer = (JSAMPIMAGE) (*cinfo.mem->alloc_small) ((j_common_ptr) &cinfo,  
			JPOOL_IMAGE, 3 * sizeof(JSAMPARRAY));   
	for(band=0; band<3; band++)
	{
		buf_width[band] = cinfo.comp_info[band].width_in_blocks * DCTSIZE;
		buf_height[band] = cinfo.comp_info[band].v_samp_factor * DCTSIZE;
		buffer[band] = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo,
				JPOOL_IMAGE, buf_width[band], buf_height[band]);
	}   

	unsigned char *rawData[3];
	rawData[0]=yuvData;
	rawData[1]=yuvData+image_width*image_height;
	rawData[2]=yuvData+image_width*image_height*5/4;

	int max_line = cinfo.max_v_samp_factor*DCTSIZE;   
	int counter;
	for(counter=0; cinfo.next_scanline < cinfo.image_height; counter++)
	{   
		//buffer image copy.
		for(band=0; band<3; band++)
		{
			int mem_size = buf_width[band];
			unsigned char *pDst = (unsigned char *) buffer[band][0];
			unsigned char *pSrc = (unsigned char *) (rawData[band] +
					counter*buf_height[band] * buf_width[band]);
			memcpy(pDst,pSrc,buf_width[band]*buf_height[band]);
#if 0
			//	for(i=0; i<buf_height[band]; i++)
			//	{
			//			memcpy(pDst, pSrc, mem_size);
			//			pSrc += buf_width[band];
			//			pDst += buf_width[band];
			//	}
#endif 

#if 0
			for(i=0; i<buf_height[band]; i++)
			{
				memcpy(pDst, pSrc, mem_size);
				pSrc += buf_width[band];
				pDst += buf_width[band];
			}
#endif 
		}
		jpeg_write_raw_data(&cinfo, buffer, max_line);
	}
	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);
}

#endif 
#if 0
int yuv420sp_to_jpg(char *filename, int width, int height, unsigned char *pYUVBuffer)
{
	FILE *fJpg;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];
	int row_stride;
	int i = 0, j = 0;
	unsigned char yuvbuf[width * 3];
	unsigned char *pY, *pU, *pV;
	int ulen;

	ulen = width * height / 4;

	if(pYUVBuffer == NULL){
		printf("pBGRBuffer is NULL!\n");
		return -1;
	}

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	fJpg = fopen(filename, "wb");
	if(fJpg == NULL){
		printf("Cannot open file %s, %s\n", filename, "hello");
		jpeg_destroy_compress(&cinfo);
		return -1;
	}

	jpeg_stdio_dest(&cinfo, fJpg);
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_YCbCr;
	cinfo.dct_method = JDCT_ISLOW;
	jpeg_set_defaults(&cinfo);


	jpeg_set_quality(&cinfo, 99, TRUE);

	jpeg_start_compress(&cinfo, TRUE);
	row_stride = cinfo.image_width * 3; /* JSAMPLEs per row in image_buffer */

	pY = pYUVBuffer;
	pU = pYUVBuffer + width*height;
	pV = pYUVBuffer + width*height + ulen;
	j = 1;
	while (cinfo.next_scanline < cinfo.image_height) {



		if(j % 2 == 1 && j > 1){
			pU = pYUVBuffer + width*height + width / 2 * (j / 2);
			pV = pYUVBuffer + width*height * 5 / 4 + width / 2 *(j / 2);
		}
		for(i = 0; i < width; i += 2){
			yuvbuf[i*3] = *pY++;
			yuvbuf[i*3 + 1] = *pU;
			yuvbuf[i*3 + 2] = *pV;

			yuvbuf[i*3 + 3] = *pY++;
			yuvbuf[i*3 + 4] = *pU++;
			yuvbuf[i*3 + 5] = *pV++;
		}

		row_pointer[0] = yuvbuf;
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
		j++;
	}

	jpeg_finish_compress(&cinfo);

	jpeg_destroy_compress(&cinfo);
	fclose(fJpg);

	return 0;
}
#endif

