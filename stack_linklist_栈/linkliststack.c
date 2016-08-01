/*************************************************************************
    > File Name: linkstack.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 07:39:26 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct node{
	datatype data;
	struct node *next;
}stacknode;/* 链表节点  */

typedef struct linkstack{
	stacknode *top;
	int count;
}linkstack;/* 栈顶指针：在栈顶操作删除添加 */

linkstack *stack_create()
{
	linkstack *H;

	if ((H =(linkstack *)malloc(sizeof(linkstack))) == NULL)
	{
		printf("linkstack malloc failed\n");
		exit(-1);
	}
	H->top = NULL;

	return H;
}

int stack_push(linkstack *H, datatype data)  /* 压栈  */
{
	stacknode *P;
	if ((P = (stacknode *)malloc(sizeof(stacknode))) == NULL)
	{
		printf("stack_push malloc failed\n");
		exit(-1);
	}
	P->next = NULL;
	P->data = data;

	P->next = H->top;
	H->top = P;
	H->count++;

	return 0;
}

int stack_pop(linkstack *H, int *e)
{
	stacknode *P;

	*e = H->top->data;
	
	P = H->top;
	H->top = H->top->next;
	
	free(P);
	H->count--;
	return 0;
}
int stack_empty(linkstack *H)
{
	return 0;
}
void stack_clear(linkstack *H)
{
	return;
}
int main(int argc, char *argv[])
{
	linkstack *H = NULL;
	int e;
	int i;

	if ((H = stack_create()) == NULL)
	{
		printf("Created failed\n");
		exit(-1);
	}
	for (i = 0; i < 10; i++)
	{
		stack_push(H,i);
	}
	
			stack_pop(H,&e);
	printf("%d\n",e);
		return 0;
}
