/*************************************************************************
    > File Name: linkstac.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 01 Jul 2016 03:01:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct Linknode{
	datatype data;
	struct Linknode *next;
}Linknode;

/* 存放栈顶指针  */
typedef struct Stacktop {
	Linknode *top;
}Stacktop;

/* 创建空栈 */
int Stack_create(Stacktop *S)
{
	Linknode *H;/* 申请节点空间  */
	if ((H = (Linknode *)malloc(sizeof(Linknode))) == NULL)
	{
		printf("Stack_create malloc failed\n");
		return -1;
	}

	S->top = H;/* 让H成为栈顶*/
	H->next = NULL;
	return 0;
}
/* 入栈  */
int Stack_push(Stacktop *S, datatype value)
{
	Linknode *H;
	if ((H = (Linknode *)malloc(sizeof(Linknode))) == NULL)
	{
		printf("push malloc failed\n");
		return -1;
	}

	H->data = value;/* 创建节点 并赋值  */

	H->next = S->top;/* 让新创建的节点连接上原来的栈顶元素  */
	S->top = H;

	return 0;
}
/* 出栈  */
int Stack_pop(Stacktop *S, datatype *value)
{
	Stacktop *Q;
	if ((Q= (Stacktop *)malloc(sizeof(Stacktop))) == NULL)
	{
		printf("push malloc failed\n");
		return -1;
	}
	Q->top = S->top;
	*value = S->top->data;

	S->top = Q->top->next;
    free(Q);
	return 0;
}
/* 判断栈的长度 */
/* 清空栈  */
/* 从栈顶依次输出 */
int main(int argc, char *argv[])
{
	Stacktop *S;
	int i, value;
	if ((S = (Stacktop *)malloc(sizeof(Stacktop))) == NULL)
	{
		printf("main Stacktop malloc failed\n");
		return -1;
	}
	Stack_create(S);
	for (i = 1; i < 10; i++)
	{
		Stack_push(S, i);
	}
	for (i = 1; i < 10; i++)
	{
		Stack_pop(S, &value);
		printf("%d  ", value);
	}
	putchar(10);
	
	return 0;
}
