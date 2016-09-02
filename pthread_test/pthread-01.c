/*************************************************************************
    > File Name: pthread-01.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 15 Aug 2016 08:17:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

static pthread_mutex_t testlock;

static void *Func(void *arg)
{
	pthread_mutex_lock(&testlock);
	char *s = (char *)arg;
	printf("%s\n", s);
	pthread_mutex_unlock(&testlock);
	return (void *)strlen(s);
}

int main(int argc, char *argv[])
{
	/* #include <pthread.h>
	 *        int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	 *                                  void *(*start_routine) (void *), void
	 *                                  *arg);
	 */
	pthread_t thread;
	void *res;
	int s;
	pthread_mutex_init(&testlock, NULL);
	pthread_mutex_lock(&testlock);
	s = pthread_create(&thread, NULL, Func, "hello world\n");
	/* 参数1 线程标识符 参数2 设置线程属性 参数3 线程函数起始地址 参数4
	 * 传给函数的参数  */
	if (s != 0)
	{
//		errExitEN(s, "pthread Created");
	}

	printf("pthread Main()\n");
	pthread_mutex_unlock(&testlock);

	s = pthread_join(thread, &res);
	if (s != 0)
	{
//		errExitEN(s, "pthread_join");
	}
	printf("pthread join\n");
	
	return 0;
}
