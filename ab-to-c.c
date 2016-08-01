/*************************************************************************
    > File Name: ab-to-c.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 22 Jul 2016 08:26:43 PM CST
 ************************************************************************/

#include <stdio.h>

int getbuf3(int *inbuf1, int *inbuf2, int *outbuf3, int inlen1, int inlen2, int *outlen)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int num = 0;
	int m;

	while(i < inlen1 && j < inlen2)/* 遍历两数组 */
	{
		if (inbuf1[i] < inbuf2[j])/* 如果1里的数组小 则把1插入数组3  */
		{
			outbuf3[k++] = inbuf1[i];
			++i;
			num++;
		}
		else if (inbuf1[i] == inbuf2[j])/* 如果相等插入任意一个都可以 */
		{
			outbuf3[k++] = inbuf1[i];
			++i;
			++j;
			num++;
		}
		else
		{
			outbuf3[k++] = inbuf2[j];/* 如果数组2元素小插入2到3  */
			++j;
			num++;
		}
	}
	if (i == inlen1)/* 若数组1遍历完 处理数组2剩下的元素 */
	{
		for (m = j; m < inlen2; m++)
		{
			outbuf3[k++] = inbuf2[m];
			num++;
		}
		
	}
	else /* 若数组2 遍历完 处理数组1剩下的元素 */
	{
		for (m = i; m < inlen1; m++)
		{
			outbuf3[k++] = inbuf1[m];
			num++;
		}
		
	}
	*outlen = num;
	return 0;
}
int main(int argc, char *argv[])
{
	int inbuf1[] = {1,5,6,13,17,23,24,56};
	int inbuf2[] = {1,2,3,5,6,9,21};
	int outbuf3[128];
	int ret, outlen;
	int i;

	int inlen1 = sizeof(inbuf1)/sizeof(int);
	int inlen2 = sizeof(inbuf2)/sizeof(int);

	ret = getbuf3(inbuf1, inbuf2, outbuf3, inlen1, inlen2, &outlen);
	if (ret < 0)
	{
		printf("return 0;\n");
		return ret;
	}
	
	for (i = 0; i < outlen; i++)
	{
		printf("%d\t",outbuf3[i]);
	}
	putchar(10);
	return 0;
}
