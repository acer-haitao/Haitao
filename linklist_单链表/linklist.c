/*************************************************************************
    > File Name: linklist.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 14 Jun 2016 04:24:24 AM PDT
 ************************************************************************/

#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>

/*-------------------------------start-------------------------------*/
linknode *linklist_create(void)
{
	linklist H = NULL;
	if((H = (linknode *)malloc(sizeof(linknode))) == NULL)
	{
		printf("malloc failed\n");
	}
	H->next = NULL;
	H->data = 0;
	return H;
}
/*--------------------------------end--------------------------------*/

/*-------------------------------start-------------------------------*/
int linklist_head_insert(linknode *H,  int value)//FILO先进后出（队列）
{
	linklist P = NULL;
	if((P = (linknode *)malloc(sizeof(linknode))) == NULL)
	{
		printf("linklist_create malloc failed\n");
		return -1;
	}
	P->data = value;
	P->next = H->next;
	H->next = P;

	return 0;
}
/*--------------------------------end--------------------------------*/

/*-------------------------------start-------------------------------*/
int linklist_show(linknode *H)
{
	while(H->next)
	{
		printf("%d\t",H->next->data);//下一节点的data
		H = H->next;
	}
	putchar(10);
	return 0;
}
/*--------------------------------end--------------------------------*/

/*-------------------------------start-------------------------------*/
int linklist_chose_insert(linklist H, int pos, int value)
{
	int i = 1;
	linklist P,Q;
	if((P = (linknode *)malloc(sizeof(linknode))) == NULL)
	{
		printf("linklist_chose_insert malloc failed\n");
		return -1;
	}
	P->data = value;
	Q = H->next;
	while(Q && i < pos)//判断Q是否为空指针
	{
		Q = Q->next;
		i++;
	}
	
	return 0;
}
/*--------------------------------end--------------------------------*/
