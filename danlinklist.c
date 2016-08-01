/*************************************************************************
    > File Name: danlinklist.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sun 17 Jul 2016 09:48:30 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node{
	datatype data;
	struct node *next;
}linknode, *linklist;

linklist create(void)
{
	linklist H = NULL;
	if ((H = (linklist)malloc(sizeof(linknode))) == NULL)
	{
		printf("malloc failed\n");
		return NULL;
	}
	H->next = NULL;
	return H;
}
int insert_linklist(linklist H, int x)
{
	linklist S = NULL;/*  创建新节点来存放要插入的数据  */
	if ((S = (linklist)malloc(sizeof(linknode))) == NULL)
	{
		printf("malloc failed\n");
		return -1;
	}
	S->data = x;

	S->next = H->next;/* 第一个节点挂在新节点上  */
	H->next = S;/* 新节点挂在头节点上  */

	return 0;
}

int show_linklist(linklist H)
{
	if (empty_linklist(H))
	{
		printf("empty_linklist\n");
	}
	while(H->next != NULL)
	{	
		H = H->next;
		printf("%p--->%d--->%c\n", H, H->data, H->data);
	}
	return 0;
}
int dele_linklist(linklist H)
{
	linklist tmp;
	int data;
	
	data = H->next->data;/* 打印第一个节点 */

	tmp = H->next;/* 保存要释放的第一个节点  */
	H->next = tmp->next;/* 让第二个节点挂在头节点上 */

	free(tmp);
	tmp = NULL;
	return data;
}
int empty_linklist(linklist H)
{
	return H->next == NULL ? 1 : 0;
}
int resver_linklist(linklist H)
{
	/* 链表反转  */
	linklist a, b;
	a = H->next; /* 保存第一个节点的地址  */
	H->next = NULL;/* 清空头节点 后面采用头插法  */

	while(a != NULL)/* 从第一个头节点开始遍历 然后用头插法挂在头节点后面  */
	{
		printf("--------------分割线--------------\n");
		b = a;
		a = a->next;/* 此时a指向第二个节点了 */
		
		b->next = H->next;/* 头插法把第一个节点挂在头节点后  */
		H->next = b;
		printf("%d--%c\n",b->data, b->data);
	}
	return 0;
}
int main(int argc, char *argv[])
{
	linklist H = create();
	insert_linklist(H, 'A');
	insert_linklist(H, 'B');
	insert_linklist(H, 'C');
	insert_linklist(H, 'D');
	insert_linklist(H, 'E');
	insert_linklist(H, 'F');

	show_linklist(H);
	printf("链表反转\n");
	resver_linklist(H);
//	printf("%d\n",dele_linklist(H));
	show_linklist(H);

	return 0;
}
