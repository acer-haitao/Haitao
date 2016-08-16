/*************************************************************************
    > File Name: pthread-01.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Mon 15 Aug 2016 08:17:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

static void *Func(void *arg)
{
	char *s = (char *)arg;
	printf("%s\n", s);

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

	s = pthread_create(&thread, NULL, Func, "hello world\n");
	/* 参数1 线程标识符 参数2 设置线程属性 参数3 线程函数起始地址 参数4
	 * 传给函数的参数  */
	if (s != 0)
	{
//		errExitEN(s, "pthread Created");
	}

	printf("pthread Main()\n");
	s = pthread_join(thread, &res);
	if (s != 0)
	{
//		errExitEN(s, "pthread_join");
	}
	printf("pthread join\n");
	
	return 0;
}
