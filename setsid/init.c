/*************************************************************************
  > File Name: init.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Sat 03 Sep 2016 03:34:03 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

/***********************************************************************
 * 主程序功能：每隔一分钟向文件中报告运行的状态 
 * 初始化程序功能：生成守护进程
 ***********************************************************************/ 
void init_daemon(void)
{
	int pid;
	int i;

	printf("我是初始函数\n");
	pid = fork();
	if (pid < 0)
	{
		printf("创建进程失败\n");
		return;
	}
	else if(pid > 0)//父进程退出
	{	
		printf("父进程退出\n");
		_exit(0);
	}
	else
	{
		printf("子进程正在设置\n");
		setsid();//子进程成为新的会话组长和进程组长，并与控制终端分离

		chdir("/tmp");//改变工作目录到tmp
		umask(0);//重设文件权限掩码
		printf("我是守护进程\n");
		for (i = 0; i < getdtablesize(); ++i)//关闭打开的文件描述符 getdtablesize（）获取最大文件描述符
		{
			close(i);
			printf("关闭文件%d\n",i);
		}

	}
	return;
}
