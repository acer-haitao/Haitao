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

#define BUF_SIZE 2048

int main(int argc, char *argv[])
{	/* 进程可以直接读写内存：效率最高 */
	/*1 ftok生成key值（作为IPC对象通信的外部名字 shmid内部名字）2 创建共享内存shmget  */
	/* 3 映射共享内存shmat 4 撤销共享内存shmdt 5 删除共享内存shmctl */
	pid_t pid;
	int shmid;
	char *shmaddr;
	char flag[] = "WROTE";
	char buf[BUF_SIZE];
	/* 创建或打开共享内存 返回shmid */
	if ((shmid = shmget(IPC_PRIVATE,BUF_SIZE, 0666)) < 0)
	{
		perror("shmget");
		exit(1);
	}
	else
	{
		printf("Created shared-memory: %d\n", shmid);
	}

	system("ipc -m");

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)/* 子进程  */
	{
		if ((shmaddr = shmat(shmid, 0, 0))  == (void *) -1) /*映射共享内存 成功返回地址 失败-1*/
		{
			perror("child : shmat");
			exit(1);
		} else
		{
			printf("child Attsch shared-memory : %p\n", shmaddr);
		}
		system("ipcs -m");

		while(strncmp(shmaddr, flag, strlen(flag)))
		{
			printf("child wait for enable data....\n");
			sleep(5);
		}


		strcpy(buf,shmaddr + strlen(flag));
		printf("child shared-memory : %s\n", buf);

		if ((shmdt(shmaddr)) < 0)/* 撤销共享内存 */
		{
			perror("shmdt");
			exit(1);
		}
		else{
			printf("child deattch shared-memory\n");
		}

		system("ipcs -m");
		

		if ((shmctl(shmid, IPC_RMID, NULL)) == -1)/* 删除共享内存 */
		{
			perror("child shmctl(IPC_RMID)");
			exit(1);
		} else
		{
			printf("delete shared-memory\n");
		}
	}
	else /* 父进程  */
	{
		/* 映射共享内存 */
		if ((shmaddr = shmat(shmid, 0, 0)) == (void *) -1)
		{
			perror("Parent: shmat\n");
			exit(1);
		} else
		{
			printf("Parent Attsch-memory %p\n", shmaddr);
		}

		sleep(1);

		printf("请输入：\n");
		fgets(buf, BUF_SIZE, stdin);
		strncpy(shmaddr + strlen(flag), buf, strlen(buf));
		strncpy(shmaddr, flag, strlen(flag));
	
		/* 解除共享内存映射 */
		if ((shmdt(shmaddr)) < 0)
		{
			perror("Parent shmdt");
			exit(1);
		} else
		{
			printf("Parent Deattch shared-memory\n");
		}

		system("ipcs -m");


		waitpid(pid, NULL, 0);
		printf("Finished\n");
	}
	
	exit(0);
	return 0;
}
