/*************************************************************************
    > File Name: msgrecv.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 24 Jun 2016 04:07:24 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define  BUF_SIZE  100


typedef struct message{
	long msg_type;
	char msg_text[BUF_SIZE];
}MSG;

/*******************************************
 * 1 通过msgid消息队列的队列ID来msgsnd(),
 *   msgrcv(), msgctl()
 * 2 key为消息对列的键值
 * 3 消息对列的实现包括四种操作：
 *   创建/打开->添加-->读取-->控制
 * 4 通过专有的结构体进行进程间的通信
 *******************************************/ 

int main(int argc, char *argv[])
{
	key_t key;
	MSG msg;
	int msgid;

	if ((key = ftok(".", 'a')) < 0)
	{
		printf("ftok failed\n");
		return -1;
	}

	if ((msgid = msgget(key,IPC_CREAT | 0666 )) < 0)/* 创建消息队列  */
	{
		printf("msgget failed\n");
		return -1;
	}

	printf("open msg queue: %d\n", msgid);

	do	
	{
		memset(msg.msg_text, 0, BUF_SIZE);
		if (msgrcv(msgid, (void *)&msg, sizeof(MSG), 0, 0) < 0)/* 读取消息队列  */
		{
			printf("rcv failed\n");
			return -1;
		}
		printf("The massage from process %ld : %s", msg.msg_type, msg.msg_text);
	}while(strncmp(msg.msg_text, "quit", 4));

	if ((msgctl(msgid, IPC_RMID, NULL)) < 0) /* 删除消息队列  */
	{
		printf("msgctl\n");
		return -1;
	}

	return 0;
}
