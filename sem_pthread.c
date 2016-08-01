/*************************************************************************
    > File Name: sem_pthread.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sun 31 Jul 2016 11:04:27 AM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSIZE  10


void provider_data();
void handler_data();

sem_t sem;
int stack[MAXSIZE];
int size;

int main(int argc, char *argv[])
{
	pthread_t provider, handler;

	sem_init(&sem, 0, 0);/* 初始化*/

	pthread_create(&provider, NULL, (void *)provider_data, NULL);
	pthread_create(&handler, NULL, (void *)handler_data, NULL);
	
	pthread_join(provider, NULL);
	pthread_join(handler, NULL);

	sem_destroy(&sem);
	return 0;
}

void provider_data()
{
	int i;
	for (i = 0; i < MAXSIZE; i++)
	{
		stack[i] = i;
		if (i == 5)
		{
			sleep(5);
		}
		sem_post(&sem);/*调用一次资源加1*/
	}
}

void handler_data()
{
	int i;
	while((i = size++) < MAXSIZE)
	{
		sem_wait(&sem);/*调用一次资源减少1 没有资源堵塞等待*/
		printf("%d X %d = %d\n", stack[i], stack[i], stack[i]*stack[i]);
	//	sleep(1);
	}
}

