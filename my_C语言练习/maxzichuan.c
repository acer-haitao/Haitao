/*************************************************************************
  > File Name: maxzichuan.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Mon 25 Jul 2016 04:25:31 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/***********************************************************************
 * for
 ***********************************************************************/ 
int getCommon(char *s1, char *s2, char **r1, char **r2)
{
	if (s1 == NULL || s2 == NULL)
	{
		printf("NULL\n");
		return -1;
	}
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int maxlen = 0;
	int i, j;
/***********************************************************************
   两层for+while
 * 思路：
 * 	   1 first层for 遍历buf1字符串 按住一个变量
 * 	   2 second层for 从buf2字符串第一个开始往后一直到尾 
 * 	   3 third层while  比较buf1和buf2遇到相等的就接着往下找
 * 	   4 abcdedf
 * 	     asgsgsd 
 * 	   5 按住a--> asgsgsd从头开始找到尾看看有没有以a开头连续的
 * 	   5 按住b--> asgsgsd从头开始找到尾看看有没有以b开头连续的
 ***********************************************************************/

	for (i = 0; i < len1; i++)
	{
		for (j = 0; j < len2; j++)/*内层循环j = 0 一直比较到j = len2*/
		{
			if (s1[i] == s2[j]) /* 如果相等 */
			{
				int as = i, bs = j, count = 1;
				while(as + 1 < len1 && bs + 1 < len2 && s1[++as] == s2[++bs])/* 查找最大长度 */
				{
					count++;
				}
				if (count > maxlen)/* 更新 */
				{
					maxlen = count;
					*r1 = s1 + i;
					*r2 = s2 + j;
				}
			}
		}	
	}
	return maxlen;
}

/***********************************************************************
 * 三层while循环
 * 找出buf1和buf2两个字符串的最大公共子串，把运算结果扔出去，
 * 被调函数在堆区分配内存，通过函数返回值把地址扔出去
 * 思路：
 * 	   1 first层while 遍历buf1字符串 按住一个变量
 * 	   2 second层while 从buf2字符串第一个开始往后一直到尾 
 * 	   3 third层while  比较buf1和buf2遇到相等的就接着往下找
 * 	   4 abcdedf
 * 	     asgsgsd 
 * 	   5 按住a--> asgsgsd从头开始找到尾看看有没有以a开头连续的
 * 	   5 按住b--> asgsgsd从头开始找到尾看看有没有以b开头连续的
 ***********************************************************************/

char *getCommon1(char *buf1, char *buf2, int *count)
{
	char *p1, *p2, *q1, *q2, *tmp;
	p1 = buf1;
	int max = 0, len;
	char *buf = NULL;

	while(*p1 != '\0') /* 外层遍历buf1 */
	{
		q1 = buf2;/*每次从头开始找*/
		while(*q1 != '\0')/* 内层遍历buf2 */
		{
			len = 0;
			p2 = p1;/*用p2 q2 来操作防止直接操作是改变指针的指向*/
			q2 = q1;/* 此处很重要每一轮比较完后重新赋值从新开始找*/
			while((*p2 != '\0') && (*q2 != '\0')) 
			/* 判断两个比较的字符是否到末尾 遍历完或者遇到不相等的退出*/
			{
				if (*p2 == *q2) /* 如果相等两指针往后移动继续比较 否则退出*/
				{
					p2++;
					q2++;
					len++;
				}
				else
				{
					break;
				}
			}
			if (len > max)
			{
				max = len;
				tmp = p1;/* 记录找到的开始位置 方便把字符串结果返回 */
			}
			q1++;/* 继续查找str2下一个元素 看有没有连续相等的  */
		}
		p1++;/* 继续查找str1下一个 看有没有连续相等的 */
	}

	*count = max;
	buf = (char *)malloc(sizeof(char)*max);
	strncpy(buf, tmp, max);

	return buf;
}

int getsame_char(char *str)
{
	int  len, i, j, max = 0;
	char *str1 = str;

	if (str1 == NULL)
	{
		printf("NULL\n");
		return -1;
	}
    len = strlen(str1);/* 此处sizeof得到的是4个字节*/
	printf("len = %d\n", len);

/***********************************************************************
 * 功能：查找一个字符串连续最大长度
 * 1 两个for循环比较--类似冒泡排序的比较
 * 2 外层比较多少趟 内层循环相邻元素依次往下比较 相等计数 不相等则比较下一组
 * 3 内存比较完后 记录
 * 思路：
 * 		1 aaabsdsddddd
 * 		2 按住一个变量a 开始往后两两比较连续相等的次数 记录最多次数
 ***********************************************************************/ 
	for (i = 0; i < len; i++)
	{
		int len1 = 1;/* 记录每一轮比接的结果*/
		for (j = i; j < len; j++)
		{
				if (str1[j] == str1[j+1])
				{
					len1++;
				}
				else
					break;
		}
		if(len1 > max)
		{
			max = len1;
		}
	}
	
	return max;
}

int main(int argc, char *argv[])
{
	char *str1 = "a1bcdefabcd123456789efag";
	char *str2 = "1adcgabcdefg123456789";
	char **buf1 = NULL;
	char **buf2 = NULL;
	char *buf3 = NULL;
	char *buf4 = NULL;
	buf1 = (char **)malloc(100);
	buf2 = (char **)malloc(100);
	buf3 = (char *)malloc(100);
	int max = 0;
	char *str = "ababb1118ababb1111";

	printf("--------------分割线--------------\n");
	printf("char *str1 = a1bcdefabcd123456789efag\n");
	printf("char *str2 = 1adcgabcdefg123456789\n");
	max = getCommon(str1, str2, buf1, buf2);
	printf("max = %d\n", max);
	strncpy(buf3, *buf1, max);
	printf("%s\n", buf3);

	printf("--------------分割线--------------\n");
	printf("char *str1 = a1bcdefabcd123456789efag\n");
	printf("char *str2 = 1adcgabcdefg123456789\n");
	buf4 = getCommon1(str1, str2, &max);
	printf("max = %d--->%s\n", max, buf4);

	printf("--------------分割线--------------\n");
	max = getsame_char(str);
	printf("%s -->The same char %d\n",str, max);

	return 0;
}
