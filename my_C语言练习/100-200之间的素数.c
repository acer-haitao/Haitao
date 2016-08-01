/*************************************************************************
    > File Name: 100-200之间的素数.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Wed 27 Apr 2016 07:30:43 AM PDT
 ************************************************************************/

#include <stdio.h>	
#include <math.h>
int main(int argc, const char *argv[])
{
	/*
	 *素数是大于1的整数，除了能被1和自身整除不能被其他整数整除
	 *算法：能被ｉ～i^(0.5)整除 如果不能整除则判断是否最接近或者等于i^(0.5)
	 * */
	int  i,j,n = 0;
	for(i = 100; i <= 200; i++)
	{
		for(j = 2;j < sqrt(i); j++)
		{	if(i % j == 0)
			break;//如果不能整除则说明不是素数
			else
				if(j > sqrt(i) - 1)
				{
					printf("%d",i);
					n++;//记录次数
					if(n % 5 == 0)//5个换一行
						printf("\n");
				}
				else 
					continue;
		}
	}
	return 0;
}
