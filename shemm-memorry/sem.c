/*************************************************************************
    > File Name: sem.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 25 Jun 2016 01:28:31 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include "shem.h"

/* 信号量的初始化函数 */
int init_sem(int sem_id, int init_value)
{
	union semun sem_union;
	sem_union.val = init_value; /* 赋初值  */

	/* 参数1：信号量标识符
	 * 参数2：信号量编号，当使用信号量集时才回被用到，通常为0就是单个信号量也是第一个信号量
	 * 参数3：对信号量的各种操作IPC_SETVAL->将信号量设置为sem_union,IPC_RMID->删除信号量
	 * * 参数4：结构体*/
	if ((semctl(sem_id, 0, SETVAL, sem_union)) == -1)
	{
		perror("信号量初始化失败");
		exit(1);
	}
	printf("信号量初始化成功\n");
	return 0;
}

/* 从系统中删除信号量  */
int del_sem(int sem_id)
{
	union semun sem_union;
	if ((semctl(sem_id, 0, IPC_RMID, sem_union)) == -1)
	{
		perror("从系统中删除信号量失败\n");
		exit(1);
	}
	printf("正在进行删除系统中的信号量\n");

	return 0;
}

/* P操作函数  */
int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;/* 单个信号量的编号应该为0  */
	sem_b.sem_op = -1;/* 表示P操作  */
	sem_b.sem_flg = SEM_UNDO;/* 系统自动释放将会在系统中残留的信号量  */
	if (semop(sem_id, &sem_b, 1) == -1)/* 通过sem_id和&sem_b地址操作结构体内容 */
	{
		perror("P操作失败");
		exit(1);
	}
	printf("正在进行P操作\n");
	return 0;
}

/* V操作函数  */
int sem_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;/* 表示V操作 */
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1)
	{ 
		perror("V操作函数");
		exit(1);
	}
	printf("正在进行V操作\n");
	return 0;
}

