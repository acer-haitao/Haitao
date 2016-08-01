/*************************************************************************
    > File Name: stack.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 21 Jun 2016 05:45:00 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define STAC_SIZE 100
typedef  int Datatype;
typedef struct node{
	Datatype *base;
	Datatype *top;
	int stacksize;

}SeqStack;
void Initial(SeqStack *s)//构造栈 进栈 出栈 取栈顶元素
{
	s->base = (Datatype *)malloc(STAC_SIZE *sizeof(Datatype));
	if(!s->base) exit(-1);
	s->top = s->base;
	s->stacksize = STAC_SIZE;
}
int IsEmpty(SeqStack *s)
{
	return s->top == s->base;
}
int IsFull(SeqStack *s)
{
	return s->top - s->base == STAC_SIZE -1;
}
int  Push(SeqStack *s, Datatype x)
{
	if(IsFull(s))
	{
		printf("栈上溢");
		exit(1);
	}
	printf("Push:%d\n",x);
	*s->top++ = x;//将栈顶指针加1后将ｘ入栈
}
Datatype Pop(SeqStack *S)
{
	if(IsEmpty(S))
	{
		printf("栈为空\n");
		exit(-1);
	}
	//printf("Pop:%d\n", *S->top);
	return *--(S->top);
}
Datatype Top(SeqStack *S)
{
	if(IsEmpty(S))
	{
		printf("栈为空\n");
		exit(-1);
	}
	return *(S->top-1);
}
void conversion(int N, int B)
{
	int i;
	SeqStack *S;
	Initial(S);

	while(N)
	{
		Push(S, N%B);//余数入栈
		N = N/B;
		printf("入栈%d\n",N);
	}
	while(!IsEmpty(S))
	{
		i = Pop(S);//然后在出栈
		printf("%d", i);
	}

}

int main(int argc, char *argv[])
{
	int n, d;
	printf("输入要转换的整数:");
	scanf("%d", &n);
	printf("输入要转换多少进制:");
	scanf("%d", &d);
	printf("转换结果：");
	printf("整数%d--->%d进制数\n",n,d);
	conversion(n, d);
	putchar(10);
	return 0;
}
