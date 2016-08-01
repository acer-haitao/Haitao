/*************************************************************************
  > File Name: pthread1.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Mon 04 Jul 2016 07:14:09 PM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define     MAX 10

pthread_t thread[2];
pthread_mutex_t mut;
int number = 0, i;

void *thread1()
{
	printf("我是线程1\n");
	for (i = 0; i < MAX; i++)
	{
		printf("线程1：number = %d\n", number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(2);
	}
	
	printf("主函数在等我完成任务吗？\n");
	pthread_exit(NULL);
}

void *thread2()
{
	printf("我是线程2....\n");
	for (i = 0; i < MAX; i++)
	{
		printf("线程2: number = %d\n", number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(3);
	}
	
	printf("线程2：主线程在等我完成任务吗？\n");
	pthread_exit(NULL);

}

void thread_wait()
{
	if (thread[0] != 0)
	{
		pthread_join(thread[0], NULL);
		printf("线程1已经结束\n");
	}
	if (thread[1] != 0)
	{
		pthread_join(thread[1], NULL);
		printf("线程2已经结束\n");
	}
}
void thread_create(void)
{
	int tmp;
	memset(&thread, 0, sizeof(thread));

	if ((tmp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)
	{
		printf("线程1创建失败\n");
	} else
	{
		printf("线程1被创建\n");
	}

	if ((tmp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)
	{
		printf("线程2创建失败\n");
	}else
	{
		printf("线程2被创建\n");
	}

}

int main(int argc, char *argv[])
{	
	/* 用默认初始化互斥锁  */
	pthread_mutex_init(&mut, NULL);
	printf("我是主函数，我正在创建线程，呵呵呵\n");
	thread_create();
	printf("我是主函数，我正在等待线程完成任务，呵呵呵\n");
	thread_wait();

	return 0;
}
