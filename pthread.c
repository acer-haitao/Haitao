/*************************************************************************
    > File Name: pthread.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 29 Jul 2016 01:38:36 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

int g_Flag = 0;
pthread_mutex_t mutex;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1();
void *thread2();
void *thread3();
void *thread4();
void *thread5();

int main(int argc, char *argv[])
{
	printf("--------------进入主函数--------------\n");
	
	pthread_mutex_init(&mutex, NULL);
	pthread_t tid1, tid2, tid3, tid4, tid5;
	void *a, *b, *c, *d;
	int rc1 = 0, rc2 = 0, rc3 = 0, rc4 = 0, rc5 = 0;
	/*参数1 线程变量名 
	 *参数2 线程属性指针 默认为ＮＵＬＬ
	 *参数3 执行函数函数的指针
	 *参数4 给执行函数传递参数
	 * */
	rc1 = pthread_create(&tid1, NULL, thread1, NULL);
	if (rc1 != 0)
	{
		printf(" %d\n", strerror(rc1));
	}

	rc2 = pthread_create(&tid2, NULL, thread2, NULL);
	if (rc2 != 0)
	{
		printf(" %d\n", strerror(rc2));
	}
	
	rc3 = pthread_create(&tid3, NULL, thread3, NULL);
	if (rc3 != 0)
	{
		printf(" %d\n", strerror(rc3));
	}
	rc4 = pthread_create(&tid4, NULL, thread4, NULL);
	if (rc4 != 0)
	{
		printf(" %d\n", strerror(rc4));
	}	
	rc5 = pthread_create(&tid5, NULL, thread5, NULL);
	if (rc5 != 0)
	{
		printf(" %d\n", strerror(rc5));
	}

	pthread_join(tid1, &a);
	pthread_join(tid2, &b);
	pthread_join(tid3, &c);
	pthread_join(tid4, &d);
	
	//pthread_cond_wait(&cond, &mutex);
	//printf("j = %d\n", *j);
	printf("main %d\n",g_Flag);
	printf("leave main\n");

	return 0;
}
void *thread1()
{


	pthread_mutex_lock(&mutex);
	printf("我是线程1\n");
	g_Flag++;
	printf("线程1--%d\n",g_Flag);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}
void *thread2()
{
	pthread_mutex_lock(&mutex);
//	if (g_Flag == 2)
//	{
//		pthread_cond_signal(&cond);
//	}
	printf("我是线程2\n");
	g_Flag++;
	printf("线程2--%d\n",g_Flag);
	pthread_mutex_unlock(&mutex);

	pthread_exit(0);
	//exit(0);
}
void *thread3()
{
	pthread_mutex_lock(&mutex);
	printf("我是线程3\n");
	g_Flag++;
	printf("线程3--%d\n",g_Flag);
	pthread_mutex_unlock(&mutex);

	pthread_exit(0);

}
void *thread4()
{
	pthread_mutex_lock(&mutex);
	printf("我是线程4\n");
	g_Flag++;
	printf("线程4--%d\n",g_Flag);
	pthread_mutex_unlock(&mutex);

	pthread_exit(0);

}
void *thread5()
{
	pthread_mutex_lock(&mutex);
	printf("我是线程5\n");
	g_Flag++;
	printf("线程5--%d\n",g_Flag);

	pthread_mutex_unlock(&mutex);

	pthread_exit(0);

}




