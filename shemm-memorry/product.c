/*************************************************************************
  > File Name: shemm-共享内存.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Thu 23 Jun 2016 10:44:14 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/ipc.h>
#include <signal.h>
#include "shem.h"

/* 忽略一些信号  */
int ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	//signal(SIGSTOP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	return 0;
}

int main(int argc, char *argv[])
{
	void *shared_memory = NULL;
	struct shm_buff *shm_buff_inst;
	int shmid, sem_id;

	//ignore_signal();/* 防止程序非正常退出 */

	sem_id = semget(ftok(".", 'a'), 1, 0666 | IPC_CREAT);
	init_sem(sem_id, 1);/* 初始值为1  */

	/* 1 创建共享内存 */
	shmid = shmget(ftok(".", 'b'), sizeof(struct shm_buff), 0666 | IPC_CREAT);
	if (shmid == -1)
	{
		perror("创建共享内存失败");
		exit(-1);
	}

	/* 2  将共享内存地址映射到当前进程地址空间  */
	shared_memory = shmat(shmid, (void *)0, 0);
	/* 参数2：指定地址(0代表OS自动分配，并把共享内存映射到调用进程的地址空间) */
	if (shared_memory == (void *) -1)
	{
		perror("映射失败");
		del_sem(sem_id);
		exit(-1);
	}
	printf("获取共享内存的地址：%X\n", (int)shared_memory);

	/* 3 获取共享内存的地址  */
	shm_buff_inst = (struct shm_buff *)shared_memory;

	/* 4 向共享内存写入数据  */
	do{
		sem_p(sem_id);
		printf("向共享内存写入数据：quit代表退出\n");
		if (fgets(shm_buff_inst->buffer, BUF_SIZE, stdin ) == NULL )
		{
			perror("fget");
			sem_v(sem_id);
			exit(-1);
		}
		shm_buff_inst->pid = getpid();
		sem_v(sem_id);
	}while(strncmp(shm_buff_inst->buffer, "quit", 4) != 0);
	
	/* 5 删除信号量  */
	del_sem(sem_id);

	/* 6 删除共享内存到当前地址空间中的映射  */
	if (shmdt(shared_memory) == -1)
	{
		perror("删除失败");
		exit(-1);
	}
	return 0;
}
