/*************************************************************************
    > File Name: pthread2.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 04 Jul 2016 08:15:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define  Thread_Num 10
#define  Repeat_Times 5
#define  Delay 4

void *thrd_func(void *arg)
{
	int thrd_num =  (int)arg;
	int delay_time = 0;
	int count = 0;

	printf("线程%d正在启动\n", thrd_num);
	for (count = 0; count < Repeat_Times; count++)
	{
		delay_time = (int)(Delay*(rand()/(double)RAND_MAX)) + 1;
		sleep(delay_time);
		printf("线程%d:job %d Delay = %d\n",thrd_num, count, delay_time);
	}
	printf("线程%d正在退出\n", thrd_num);
	pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
	pthread_t thread[Thread_Num];
	int no;
	void *ret;
	srand((int)time(0));

	for (no = 0; no < Thread_Num; no++)
	{
		if ((pthread_create(&thread[no], NULL, thrd_func, (void *)no)) != 0)
		{
			printf("创建线程%d失败\n", no);
		} else
		{
			printf("创建线程%d成功\n", no);
		}
	}
	for (no = 0; no < Thread_Num; no++)
	{
		if ((pthread_join(thread[no], &ret)) != 0)
		{
			printf("等待线程%d结束失败\n", no);
		} else
		{
			printf("等待线程%d结束成功\n", no);
		}
	}
	return 0;
}
