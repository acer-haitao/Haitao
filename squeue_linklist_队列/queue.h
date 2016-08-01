/*************************************************************************
    > File Name: queue.h
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 25 Jun 2016 10:50:50 PM PDT
 ************************************************************************/
#include <stdlib.h>

typedef  int datatype;

/* 定义节点存储入队元素和指向下一节点的指针  */
typedef struct node{
	datatype data;
	struct node *next;
}NODE;

/* 定义节点存放队尾和对首指针  */
typedef struct poiner{
	NODE *front;
	NODE *rear;
}Linknode;

/* 创建队列以及初始化函数  */
void created(Linknode *H);

/* 入队函数  */
void enqueue(Linknode *H, int data);

/* 出队函数  */
datatype dequeue(Linknode *H);

/* 显示队列中元素  */
void display(Linknode H);


