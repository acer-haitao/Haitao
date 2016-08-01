/*************************************************************************
    > File Name: insert直接插入排序.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sun 24 Apr 2016 08:09:20 AM PDT
 ************************************************************************/

#include <stdio.h>
void insort(int s[], int n)
{
	int i,j;
	printf("\n++++++++++++++\n");
	for(i = 0; i<10; i++)
	{
		printf("%d  ",s[i]);
	}
	for(i = 2; i <= 2; i++)
	{
		s[0] = s[i];//?
		j = i - 1;
		printf("11%d s[1] = %d\n",s[0],s[1]);
		while(s[0] < s[j])//?
		{
			s[j + 1] = s[j];
			j--;
		}
		s[j + 1] = s[0];
	}

}
int main(int argc, const char *argv[])
{
	int a[11],i;
	printf("请输入10个数字\n");
	for(i = 1; i <= 10; i++)
	{
		scanf("%d",&a[i]);
	}
	for(i = 1; i<=10; i++)
	{
		printf("%d  ",a[i]);
	}
	insort(a,10);
	printf("\n排序后：\n");
	for(i = 1; i<=10; i++)
	{
		printf("%d  ",a[i]);
	}
	putchar(10);
	return 0;
}

