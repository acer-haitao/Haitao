/*************************************************************************
    > File Name: secondfind.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 30 Jul 2016 11:02:01 AM CST
 ************************************************************************/

#include <stdio.h>
int get_secondfind(int key, int buf[], int n)
{
	int low = 0;
	int hight = n - 1;
	int conut = 0, count1 = 0;
	int mid;

	while(low < hight)
	{
		conut++;
		mid = (hight - low)/2 + low;
		if (key < buf[mid])/* 查找左边*/
		{
			hight = mid -1;
		}
		else if (key > buf[mid]) /* 查找右边  */
		{
			low = mid + 1;
		}
		else if (key == buf[mid])
		{
			printf("查找成功,查找%d次,buf[%d] = %d\n", conut, mid, key);
			count1++;
			break;
		}
	
	}
	if (count1 == 0)
	{
		printf("没找到\n");
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int buf[10];
	int i, key;
	printf("请输入10个有序数字\n");
	for (i = 0; i <10; i++)
	{
		scanf("%d", &buf[i]);
	}
	puts("您输入的数组为：");
	for (i = 0; i <10; i++)
	{
		printf("%d ", buf[i]);
	}
	putchar(10);
	printf("请输入要查找的数字\n");
	scanf("%d", &key);
	get_secondfind(key, buf, 10);
	
	return 0;
}
