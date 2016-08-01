/*************************************************************************
    > File Name: quicksort.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 03:00:10 PM CST
 ************************************************************************/

#include <stdio.h>

int qusort(int s[], int start, int end)
{
	int i, j;
	i = start;/* 将每组首个元素赋值给i  */
	j = end;/* 	将每组末尾元素赋值给j  */
	s[0] = s[start];/* 设置基准值 */
	while(i < j)
	{
		while(i < j && s[0] < s[j]) j--;/* 位置左移 */
		if (i < j)
		{
			s[i] = s[j];
			i++;
		}
		while(i < j && s[i] <= s[0]) i++;
		if (i<j)
		{
			s[j] = s[i];
			j--;
		}
		s[i] = s[0];
		if (start < i)
		{
			qusort(s, start, j - 1);
		}
		if (i < end)
		{
			qusort(s, j + 1, end);
		}
	}

	return 0;
}
int main(int argc, char *argv[])
{
	int a[11], i;
	printf("请输入10个整数\n");
	for (i = 0; i < 10; i++)
	{
		scanf("%d",&a[i]);
	}
	qusort(a, 1, 10);
	printf("排序后：\n");
	for (i = 0; i < 10; i++)
	{
		printf("%d ",a[i]);
	}
	putchar(10);
	return 0;
}
