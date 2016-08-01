/*************************************************************************
    > File Name: main.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 25 Jun 2016 10:50:34 PM PDT
 ************************************************************************/

#include <stdio.h>
#include "queue.h"
int main(int argc, char *argv[])
{
	int comand;
	Linknode *H;
	int num;
	int value;
	int i;
	H =(Linknode *)malloc(sizeof(Linknode));
	if (H == NULL)
	{
		printf("malloc failed\n");
		return -1;
	}
	do{
		printf("\n");
		printf("		1 创建队列\n");
		printf("		2 向队列插入元素\n");
		printf("		3 从队列删除元素\n");
		printf("		4 显示队列中元素\n");
		printf("		5 退出\n");
		printf("-------------------------------\n");
		printf("请输入对应操作的数字（1 2 3 4 5）\n");
		scanf("%d", &comand);
		switch (comand)
		{
		case 1:
					created(H);
			printf("请输入你要创建元素的个数:\n");
			scanf("%d", &num);
			for (i = 1; i <= num; i++ )
			{ 
				scanf("%d",&value);
				enqueue(H, value);
			}
			
			break;
		case 2:
			puts("输入你想要插入的元素:\n");
			scanf("%d", &value);
			enqueue(H, value);
			break;
		case 3:
			printf("outqueue-data:%d\n",dequeue(H));
			break;
		case 4:
			display(*H);
			break;
		case 5:
			printf("正在退出....\n");
			return 0;
		default:
			printf("请检查你的输入是否有误\n");
			return -1;
		}
	
	}while(1);
	return 0;
}
