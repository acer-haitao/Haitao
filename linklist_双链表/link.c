/*************************************************************************
    > File Name: link.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 20 Jun 2016 11:14:24 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char name[20];
	struct node *prior, *next;
}stud;

stud *Created(int n);
stud *search(stud *h, char *x);
void del(stud *p);

int main(int argc, char *argv[])
{
	int number;
	char sname[20];
	stud *head, *sp;

	puts("请输入链表的大小");
	scanf("%d", &number);
	head = Created(number);
	sp = head->next;
	printf("\n现在这个双链表是:\n");
	while(sp)
	{
		printf("%s\t", &*(sp->name));
		sp = sp->next;
	}

	printf("\n请输入你想查找的姓名:\n");
	scanf("%s", sname);

	sp = search(head, sname);
	printf("您想查找的姓名是:%s\n", *&sp->name);
	del(sp);
	sp = head->next;
	printf("\n现在这个双链表是:\n");
	while(sp)
	{
		printf("%s\t", &*(sp->name));
		sp = sp->next;
	}
	printf("\n");
	return 0;
}

stud *Created(int n)
{
	stud *p, *h, *s;//定义3个辅助指针变量
	int i;

	h = (stud *)malloc(sizeof(stud));//malloc创建头节点并初始化
	h->name[0] = '\0';
	h->prior = NULL;
	h->next = NULL;

	p = h;//Ｐ指针用来移动 开始指向头节点
	for(i = 0; i < n; i++)
	{
		s = (stud *)malloc(sizeof(stud));//循环malloc新的节点
		p->next = s;//头插法让s挂在ｐ后面
		
		printf("请输入第%d个学生的姓名：", i + 1);
		scanf("%s", s->name);

		s->prior = p;//ｓ指定前驱节点
		s->next = NULL;

		p = s;//让ｓ成为当先节点 ｐ往后移动
	}

	p->next = NULL;
	return h;
}
stud *search(stud *h, char *x)
{
	stud *p;
	char *y;

	p = h->next;//初始让ｐ指向第一个节点
	while(p)
	{
		y = p->name;//比较第一个节点和输入的姓名是否相等
		if(strcmp(y,x) == 0)
		{
			return p;
		}
		else
			p = p->next;
	}
	printf("没有找到数据\n");
}

void del(stud *p)
{
	p->next->prior = p->prior;//先搞定p的后继节点的前驱
	p->prior = p->next;//再搞定p的前驱节点的后继
	free(p);
}

