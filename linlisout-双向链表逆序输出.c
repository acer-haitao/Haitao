/*************************************************************************
    > File Name: linlisout-双向链表逆序输出.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 21 Jun 2016 05:07:27 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	char name[20];
	struct node *prior, *next;
}stu;

stu *Created(int num);
stu *output(stu *q);//获取双向链表的尾节点指针

stu *Created(int num)
{
	stu *p, *h, *s;
	int i = 0;

	h =(stu *)malloc(sizeof(stu));
	h->name[0] = '\0';
	h->next = NULL;
	h->prior = NULL;

	p = h;
	for (i = 0; i< num; i++)
	{
		s = (stu *)malloc(sizeof(stu));
		
		printf("请输入第%d个姓名\n", i);
		scanf("%s", s->name);
		p->next = s;
		s->prior = p;
		s->next = NULL;

		p = s;
	}
	p->next = NULL;
	return h;
}
stu *output(stu *q)//获取双向链表的尾节点指针
{
	stu *p, *r;
	p = q;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}
int main(int argc, char *argv[])
{	
	int i = 0;
	stu *q;

	puts("输入插入节点的个数");
	scanf("%d", &i);
	q  = Created(i);
	q  = output(q);
	
	printf("输出结果：\n");
	while(q)
	{
		printf("%s\t", q->name);
		q = q->prior;
	}

	return 0;
}
