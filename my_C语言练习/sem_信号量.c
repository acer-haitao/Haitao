/*************************************************************************
    > File Name: sem_信号量.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 24 Jun 2016 05:33:56 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

#define  DELAY_TIME  5

/***********************************************************************
 * 1 信号量来解决线程/进程之间同步和互斥问题的一种通信机制
 * 2 包括： 一个称为信号量的变量 + 该信号量下等待资源的进程等待队列
 * 3 信号量的值 = 0  说明当前没有可用资源
 * 4 操作步骤：
 *   创建或获取系统已存在的信号量semget()-->返回信号量标识符sem_id
 *	 初始化信号量semctl()-->SETVAL
 *	 进行信号量的ＰＶ操作semop()
 *	 如果不需要信号量，从系统中删除semctl()-->IPC_RMID
 * 5 怎么获取信号量？-->不同进程通过同一个信号量的键值来获取同一个信号量
 ***********************************************************************/

/* semctl操作要用的结构体  */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
#if 0
/* semop操作要用的结构体  */
struct sembuf{
	short sem_num;/* 信号量的编号，使用单个信号量时通常取0 */
	short sem_op;/* 信号量操作：取值为-1表示Ｐ操作，+为Ｖ操作 */
	short sem_flg;/* 通常设置为SEM_UNDO，这样在进程没有释放信号量而退出时，系统自动释放 */
};
#endif
/* 信号量的初始化函数 */
int init_sem(int sem_id, int init_value)
{
	union semun sem_union;
	sem_union.val = init_value; /* 赋初值  */

	/* 参数1：信号量标识符
	 * 参数2：信号量编号，当使用信号量集时才回被用到，通常为0就是单个信号量也是第一个信号量
	 * 参数3：对信号量的各种操作IPC_SETVAL->将信号量设置为sem_union,IPC_RMID->删除信号量
	 * 参数4：结构体*/
	if ((semctl(sem_id, 0, SETVAL, sem_union)) == -1)
	{
		perror("信号量初始化失败");
		exit(1);
	}
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
	return 0;
}

/***********************************************************************
 *主函数： 创建子进程-->使用信号量来控制两个进程的执行顺序
 *PV操作：
 *		P: 如果有可用资源(信号量>0)，则占用一个资源(信号量-1,进入临界区代码)；
 *	如果没有可用资源(=0)，则被阻塞直到系统将资源分配给该任务(进入等待队列，
 *	一直到有资源时被唤醒)
 *	    V: 如果该信号量的等待队列中有任务在等待资源，则唤醒一个阻塞任务，
 *	如果没有任务等待它，则释放一个资源(+1)
 ***********************************************************************/ 
int main(int argc, char *argv[])
{
	pid_t result;
	int sem_id;
	sem_id = semget(ftok(".", 'a'), 1, 0666 | IPC_CREAT);/* 创建一个信号量 */
	init_sem(sem_id, 0);/* 对信号量初始化  */

	result = fork();
	if (result == -1)
	{
		perror("创建子进程失败");
		exit(1);
	} 
	else if(result == 0)
	{
		printf("子进程正在等待中....\n");
		sleep(DELAY_TIME);
		printf("返回的子进程PID = %d result = %d\n", getpid(), result);
		sem_v(sem_id);
	}
	else
	{
		sem_p(sem_id);/* P操作 */
		printf("返回父进程PID = %d result = %d\n", getpid(), result);
		sem_v(sem_id);/* V操作 */
		del_sem(sem_id);
	}
	return 0;
}
