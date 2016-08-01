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
	return 0;
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
int match(SeqStack *s, char *str)
{
	char x;
	int i, flag = 1;
	for (i = 0; str[i] != '\0'; i++)
	{
		switch (str[i])
		{
		case '(':
			Push(s, '(');
			break;
		case '[':
			Push(s, '[');
			break;
		case '{':
			Push(s, '{');
			break;
		case ')':
			x = Top(s);
			Pop(s);
			if (x != '(')
			{
				flag = 0;
			}
			break;
		case ']':
			x = Top(s);
			Pop(s);
			if (x == '[')
			{
				flag = 0;
			}
			break;
		case '}':
			x = Top(s);
			Pop(s);
			if (x == '}')
			{
				flag = 0;
			}
			break;
		if (!flag)
				break;
	}
}
if (IsEmpty(s) == 1 && flag)
{
	return 1;
}
else 
return 0;
}

int main(int argc, char *argv[])
{
	SeqStack *st;
	st = (SeqStack *)malloc(sizeof(SeqStack));
	char str[100];

	Initial(st);
	gets(str);
	if (match(st, str))
	{
		printf("matching\n");
	}
	else
		printf("no matching\n");
	return 0;
}

