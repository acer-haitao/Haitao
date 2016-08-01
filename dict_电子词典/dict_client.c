#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  N  16
#define  R  1   //  user register
#define  L  2   //  user login
#define  Q  3   //  query word
#define  H  4   //  history record

#define DATABASE "my.db"

typedef struct 
{
    int type;
    char name[N];
    char data[256];   // password or word or remark
} MSG;

void do_register(int socketfd, MSG *msg);
int do_login(int socketfd, MSG *msg);
void do_query(int socketfd, MSG *msg);
void do_history(int socketfd, MSG *msg);

int main(int argc, char *argv[])
{
	printf("你好你啊哈个爸爸那\n");
    int socketfd ;
    struct sockaddr_in server_addr;
    MSG msg;
    if (argc < 3)
    {
        printf("Usage : %s <serv_ip> <serv_port>\n", argv[0]);
        exit(-1);
    }
    if ((socketfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("fail to socket");
        exit(-1);
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("fail to connect");
        exit(-1);
    }
    int n;
    while(1)
    {
        printf("****************************************************\n");
        printf("* 1: register 注册  2: login 登录   3: quit 退出\n");
        printf("****************************************************\n");
        printf("please choose : ");

        if(scanf("%d", &n) <= 0)
        {
            perror("please check your input:");
            exit(-1);
        }

        switch(n)
        {
            case 1:
                do_register(socketfd, &msg);
                break;
            case 2:
                if(do_login(socketfd, &msg) == 1)
                    goto next;
                break;
            case 3:
                close(socketfd);
                exit(0);
			default:
				printf("please check your input\n");
        }
    }
next:
    while(1)
    {
        printf("************************************\n");
        printf("* 1: query   2: history   3: quit *\n");
        printf("************************************\n");
        printf("please choose : ");

        if(scanf("%d", &n) <= 0)
        {
            perror("scanf");
            exit(-1);
        }
        switch(n)
        {
            case 1:
                do_query(socketfd, &msg);
                break;
            case 2:
                do_history(socketfd, &msg);
                break;
            case 3:
                close(socketfd);
                exit(0);
        }
    }
    return 0;
}
void do_register(int socketfd, MSG *msg)
{   
	char buf[256] = {0};
	printf("please input your name:\n");
	scanf("%s", msg->name);
	printf("please input your password:\n");
	scanf("%s",msg->data);
	msg->type = R;
	
	send(socketfd, msg, sizeof(MSG), 0);

	recv(socketfd, buf, sizeof(buf), 0);
	printf("%s\n", buf);
}
int do_login(int socketfd, MSG *msg)
{	
	puts("please input your name:");
	scanf("%s",msg->name);
	puts("please input your password:");
	scanf("%s",msg->data);
	msg->type = L;

	send(socketfd, msg, sizeof(MSG), 0);

	recv(socketfd, msg, sizeof(MSG), 0);

	if(strncmp(msg->data, "login sucess", 12) == 0)
	{
		printf("%s\n",msg->data);
		return 1;
	}
	else
	{
		printf("%s\n",msg->data);
	}

    return 0;
}
void do_query(int socketfd, MSG *msg) 
{	
	msg->type = Q;
	puts("please input your world");
	while(1)
	{
		scanf("%s",msg->data);
		if(strncmp(msg->data, "#", 1) == 0) break;
		send(socketfd, msg, sizeof(MSG), 0);
		recv(socketfd, msg, sizeof(MSG), 0);
		printf("%s\n",msg->data);
	}
	return ;
}
void do_history(int socketfd, MSG *msg)
{
	msg->type = H;//告诉server我要做什么把你要做的事情写入结构体
	send(socketfd, msg, sizeof(MSG), 0);//把结构体地址发给server
	while(1)
	{
		recv(socketfd, msg, sizeof(MSG), 0);
		if(msg->data[0] == '\0') break;
		printf("%s\n",msg->data);
	}
	return ;
}
