/*************************************************************************
    > File Name: 统计文本中单词的个数-链表.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 19 Aug 2016 09:11:20 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max_word 30

typedef struct word{
	char w[Max_word];
	int count;
	struct word *next;
}link;

int count = 0;
link *head = NULL;
FILE *fp;
int big = 0, small = 0, space = 0, num = 0, other = 0, hang_num = 0;

/*-------------------------判断是否为字母----------------------------------*/
int if_word(char a)
{
	if (a <= 'z' && a >= 'a')
	{	
		small++;
		return 0;
	}
	else if (a <= 'Z' && a >= 'A')
	{
		big++;
		return 0;
	}
	else if (a == ' ')
	{
		space++;
		return 1;
	}
	else if (a >= '1' && a <= '9')
	{
		num++;
		return 1;
	}
	else if (a == '\n')
	{
		hang_num++;
		return 1;
	}
	else
	{
		other++;
		return 1;
	}
	return 0;
}

/*-------------------------------添加单词-------------------------------*/
void addword(char *w1)
{
	link *p1, *p2;

	for (p1 = head; p1 != NULL; p1 = p1->next)
	{
		if (!strcmp(p1->w, w1))/*遍历链表单词存在+1*/
		{
			p1->count++;
			return;
		}
	}

	p1 = (struct word *)malloc(sizeof(link));/*不存在添加单词*/
	strcpy(p1->w, w1);
	p1->count = 1;
	p1->next = NULL;
	count++;//总的单词数加1

	if (head == NULL)
	{
		head = p1;
	}
	else
	{
		for (p2 = head; p2->next != NULL; p2 = p2->next)//遍历
		{
		}
		p2->next = p1;//插入链表尾部
	}
}

/*-------------------------------统计单词-------------------------------*/
void wordcount()
{
	int i = 0, j = 0;
	char word[Max_word], c;
	while(!feof(fp))
	{
		fscanf(fp, "%c", &c);
		if (if_word(c))//字母返回0 非字母返回1
		{
			word[j] = '\0';
			if (j > 0)
			{
				addword(word);
			}
			j = 0;
		}
		else 
		{
			word[j] = c;
			j++;
		}
	}

	return ;
}

/*-------------------------------读取文件中的单词-------------------------------*/
void readword()
{
	char name[20];
	printf("请输入要读取文件的名字test.txt\n");
	scanf("%s", name);
	getchar();
	if ((fp = fopen(name, "r+")) == NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	wordcount();
	fclose(fp);
}

/*-------------------------------显示单词情况-------------------------------*/
void show(int a, int b)
{
	link *p;
	printf("个数\t单词\t频率\n");

	for (p = head; p != NULL; p = p->next)
	{
		if ((p->count > a) && (p->count < b))
		{
			printf("%s\t %d\t %.2f\n",p->w, p->count, (float)(p->count)/count);
		}
	}
	printf("总的单词数：%d\n", count);
	printf("总共有%d行\n",hang_num + 1);
	printf("总共有%d字符\n",big+small+space+num+other);
	printf("大写字母%d 小写字母%d 空格%d 数字%d 其他%d\n", big, small, space, num, other);
	return;
}
/*-------------------------------main-------------------------------*/
int main(int argc, char *argv[])
{
	readword();
	int a, b;
	printf("请输入阀值eg > 2 10:");
	scanf("%d %d", &a, &b);
	getchar();
	show(a, b);
	getchar();
	return 0;
}
