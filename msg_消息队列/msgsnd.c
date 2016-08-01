/*************************************************************************
    > File Name: msgsnd.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 24 Jun 2016 03:31:34 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>

#define BUF_SIZE 100

typedef struct message{
	long msg_type;
	char msg_text[BUF_SIZE];
}MSG;


int main(int argc, char *argv[])
{
	/* 在消息队列(内核里的链表） */
	key_t key;
	int msgid;/* 消息队列ID */
    MSG msg;

	if ((key = ftok(".", 'a')) < 0)
	{
		printf("ftok failed\n");
		return -1;
	}
	if ((msgid = msgget(key, IPC_CREAT | 0666)) < 0)
	{
		printf("msgget failed\n");
		return -1;
	}
	printf("open queue : %d\n", msgid);

	while(1)
	{
		printf("请输入信息存入结构体文本成员：\n");
		if ((fgets(msg.msg_text, BUF_SIZE, stdin)) == NULL)
		{
			puts("no message");
			return -1;
		}
		msg.msg_type = getpid();
		/* 添加消息到队列(结构体首地址) */
		if ((msgsnd(msgid, &msg, strlen(msg.msg_text), 0)) < 0)
		{
			printf("msgsnd failed\n");
			return -1;
		}
		if ((strncmp(msg.msg_text, "quit", 4)) == 0)
		{
			break;
		}
	}
		return 0;
}
