/*************************************************************************
    > File Name: 2jizhizhenmalloc.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 25 Jul 2016 10:04:22 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 第一种  */
int myArray1(char **myArray, int num)
{
	int m,n;	
	char *tmp1;

	for (m = 0; m < num; m++)
	{
		for (n = m + 1; n < num; n++)
		{
			if (strcmp(myArray[m], myArray[n]) > 0)
			{
				tmp1 = myArray[m];
				myArray[m] = myArray[n];
				myArray[n] = tmp1;
			}
		}	
	}
	return 0;
}

int print2(char **myArray, int num)
{
	int m;

	for (m = 0; m < num; m++)
	{
		printf("%s\n", myArray[m]);
	}

	return 0;
}

/* 第三种  */
int sort(char **p2, int num)
{
	/* 第三种内存模型排序  */
	char *tmp = NULL;
	int i, j;
	for (i = 0; i < num; i++)
	{
		for (j = i + 1; j < num; j++)
		{
			if (strcmp(p2[i], p2[j]) < 0)/* 交换指针 */
			{
				tmp = p2[i];
				p2[i] = p2[j];
				p2[j] = tmp;
			}
		}
	}
	
	return 0;
}

char **getMer(int num)
{
	/* 第三种内存模型  */
	int i;
	char **p2 = NULL;
	p2 = (char **)malloc(sizeof(char *) * num);
	if (p2 == NULL)
	{
		return NULL;
	}

	for (i = 0; i < num; i++)
	{
		p2[i] = (char *)malloc(sizeof(char) * 100);
		sprintf(p2[i], "%d%d%d", i+1, i+1, i+1);
	}

	return p2;
}

int printMer(int num, char **p2)
{
	int i;
	for (i = 0; i < num; i++)
	{
		printf("%s	\n", p2[i]);
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	
	/***********************************************************************
	 * 二级指针做输入第一种内存模型
	 ***********************************************************************/ 
	printf("--------------1--------------\n");
	char *myArray[] = {"aaa", "bbb", "ccc", "222"};/* 指针数组 二级指针做输入 */
	/* 打印 + 排序 */
	int num1 = sizeof(myArray)/sizeof(myArray[0]);

	print2(myArray, num1);
	myArray1(myArray, num1);
	printf("排序后\n");
	print2(myArray, num1);

	/***********************************************************************
	 * *二级指针做输入第2种模型
 	***********************************************************************/ 
	printf("--------------2--------------\n");
	char buf[10][30] = {"aaafaf","agaafjkal","agdadkjgawe"};
	char buf2[30], tmp[30];
	int a, b, i;
		
	for (i = 0; i < 3; i ++)
	{
		printf("%s\n", buf[i]);
	}

	for (a = 0; a < 3; a++)
	{
		for (b = a +1; b < 3; b++)
		{
			if (strcmp(buf[a], buf[b]) < 0)
			{
				strcpy(tmp, buf[a]);
				strcpy(buf[a], buf[b]);
				strcpy(buf[b], tmp);
			}
		}
	}
	printf("排序后\n");
	for (i = 0; i < 3; i ++)
	{
		printf("%s\n", buf[i]);
	}
	
	/***********************************************************************
	 * 二级指针做输入第3种内存模型
	 ***********************************************************************/ 
	printf("------------3--------------\n");
	char **p2 = NULL;
	int num = 5;
	p2 = getMer(num);
	printMer(num, p2);
	printf("排序后\n");
	sort(p2, num);	
	printMer(num, p2);

	return 0;
}
