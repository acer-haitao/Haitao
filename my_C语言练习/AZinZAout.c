/*************************************************************************
    > File Name: AZinZAout.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sun 17 Jul 2016 12:28:16 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef char datatype;
typedef struct node {
	datatype data;
	struct node *next;
}linknode, *linklist;

linklist create(void)
{
	linklist H;

	if ((H = (linklist)malloc(sizeof(linknode))) == NULL)
	{
		printf("malloc failed\n");
		return NULL;
	}
	H->next = NULL;

	return H;
}

int linklist_insert(linklist H, datatype x)
{
	linklist P;

	if ((P = (linklist)malloc(sizeof(linknode))) == NULL)
	{
		printf("malloc failed\n");
		return -1;
	}
	P->data = x;

	P->next = H->next;
	H->next = P;
	return 0;
}


int linklist_reserv(linklist H)
{
	linklist q, p;
	q = H->next;
	H->next = NULL;

	while(q != NULL)
	{
		p = q;
		q = q->next;

		p->next = H->next;
		H->next = p;
	}
	return 0;
}

int linlist_show(linklist H)
{
	int i = 1;
	if (linklist_empty(H))
	{
		printf("empty\n");
		return -1;
	}

	while(H->next != NULL)
	{	
		H = H->next;
		printf("%d---%c\n", i++,H->data);
	}

	return 0;
}

int linklist_empty(linklist H)
{
	return H->next == NULL ? 1:0;
}

int main(int argc, char *argv[])
{
	linklist H = create();
	int i = 0;

	for (i = 0; i < 26; i++)
	{
		linklist_insert(H, 'A' + i);
	}
	linlist_show(H);
	printf("--------------分割线--------------\n");
	linklist_reserv(H);
	linlist_show(H);
	return 0;
}

