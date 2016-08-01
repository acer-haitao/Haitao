/*************************************************************************
    > File Name: main.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 14 Jun 2016 04:24:24 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(int argc, const char *argv[])
{
	linklist H = NULL;
	if((H = linklist_create()) ==NULL)
	{
		printf("Created failed\n");
		return -1;
	}
	linklist_head_insert(H, 1);
	linklist_head_insert(H, 2);
	linklist_head_insert(H, 3);
	linklist_head_insert(H, 4);
	linklist_head_insert(H, 5);
	linklist_head_insert(H, 6);
	linklist_head_insert(H, 7);
	linklist_head_insert(H, 8);

	linklist_show(H);

	return 0;
}
