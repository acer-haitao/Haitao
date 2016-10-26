/*************************************************************************
  > File Name: main.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Tue 25 Oct 2016 11:56:51 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define N 1024

int main(int argc, char *argv[])
{
	int i = 0;
	char Newfile[N] = {0};
	char buf[N] = { 0 };
	char update[N] = { 0 }; 
	
	for(i = 0; i < 2; i++)
	{
		sprintf(Newfile, "Prescription2016092300%d.xml",i);
		FILE *in=fopen("Prescription2016092300101.xml","r");
		FILE *out=fopen(Newfile,"w");  /*out是充当临时文件作用*/
		int linesize = 0;
		char *p = NULL;

		if(!in)
		{
			printf("cann't open test.txt\n");
			return -1;
		}
		if(!out)
		{
			printf("cann't create back.txt\n");
			return -1;
		}
		/*开始复制*/
#if 0
		while(!feof(in))
		{
			ch=fgetc(in);
			if(ch=='a') ch='p';
			fputc(ch,out);
		}
#endif
		while(fgets(buf, N, in) != NULL)
		{
#if 1
			linesize = strlen(buf);
			printf("%d\n",linesize);
			if(buf[linesize - 1] == '\n')
			{
			//	printf("HELLs\n");
				buf[linesize - 1] = '\0';
			}
#endif
			if ((p = strstr(buf, "测试")) != NULL)
			{
				//	printf("%s\n", p);
				sprintf(update, "<PATIENT_NAME>测试%d</PATIENT_NAME>\n", i);
				//	fwrite(update, linesize, 1, out);
				fputs(update, out);
			}
			else if((p = strstr(buf, "<PATIENT_ID>")) != NULL)
			{
				sprintf(update, "<PATIENT_ID>%d</PATIENT_ID>\n", i);
				fputs(update, out);
			}
			else if((p = strstr(buf, "PRESCRIPTION_ID=")) != NULL)
			{
				//	printf("%s\n",p);
				sprintf(update, " <PRESCRIPTION PRESCRIPTION_ID=\"2016092300%d\" PRESCRIPTION_DATE_TIME=\"2016-03-17T00:00:00\" ORDERED_BY=\"中医科门诊\" PRESCRIBER=\"任芳\" PRESCRIPTION_SOURCE=\"0\" DIAGNOSIS=\"乏力(气血两虚)\">",i);
				//	fwrite(update, N, buf);
				fputs(update, out);
			}
			else
			{
				//	fwrite(buf, linesize, 1, out);
				fputs(buf, out);
			}
		}

		fclose(in);  
		fclose(out);  

#if 1
		unlink(Newfile); /*删除test.txt*/
		//	rename("f:\\back.txt","test.txt"); /*改名*/
#endif
		printf("Prescription2016092300%d---->ok!!!!!!\n",i);
	}
	return 0;
}

