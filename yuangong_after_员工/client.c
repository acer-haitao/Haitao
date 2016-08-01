#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define N      64
#define READ   1   //查询用户信息
#define CHANGE 2   //修改用户信息
#define DELETE 3   //删除用户
#define ADD    4   //添加用户
#define LOAD   5   //用户申请登录
#define QUIT   6   //用户退出时发给服务器的通知消息
#define SUCCESS  7 //服务器操作成功
#define FAILED   8 //服务器操作失败


#define STAFF  10
#define ADM    11

typedef struct
{
	int  type;//判断是否为管理员
	char name[N];
	char password[N];
	int no;
}USER;

typedef struct
{
	char name[N];//姓名
	char addr[N];//地址
	int  age;//年龄
	int  level;//评级
	int  no;//编号
	double  salary;//工资
	char phone[N];//手机号
	int type;//员工级别

}INFO;

typedef struct{
	int sign;
	int type;//判断操作类型
	char name[N];//发送消息的户
	INFO info;//员工信息结构体
	char password[N];//用户密码在第一次登录时使用）
	char data[N];//操作成功或者失败的消息
}MSG;
int client_addusr(int socketfd,MSG *msg);

int main(int argc, char *argv[])
{
	printf("你好<--客户端-->世界\n");
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
	while(1)
	{
		printf("************************************\n");
		printf("   *    请输入用户名和密码    *\n");
		printf("************************************\n");

		printf("请输入用户名:");
		fgets(msg.name, N, stdin);
		msg.name[strlen(msg.name) - 1] = '\0';

		printf("请输入用户密码:");
		fgets(msg.password, N, stdin);
		msg.password[strlen(msg.password) - 1] = '\0';//?
		msg.type = LOAD;

		send(socketfd, &msg, sizeof(MSG), 0);
		printf("正在登录中请稍候.....\n");
		recv(socketfd, &msg, sizeof(MSG), 0);
		if(msg.sign == FAILED)
		{
			/*登录失败*/
			printf("%s", msg.data);
			continue;
		}

		if(msg.sign == SUCCESS)
		{
			/*登录成功*/
			if(msg.info.type == STAFF)
			{
				goto Usr;
			}
			else if(msg.info.type == ADM)
			{
				goto Admin;
			}
		}
	}

Usr:
	while(1)
	{
		printf("普通用户\n");
		printf("************************************\n");
		printf("    1查询 2修改密码 3退出*\n");
		printf("************************************\n");

	}

Admin:
	while(1)
	{
#if 1

		printf("管理员\n");
		printf("*****************************************\n");
		printf(" 1增加用户 2删除用户 3查询 4修改 5退出  *\n");
		printf("*****************************************\n");
		int result;
		int command;
		char clear[N];
		if(scanf("%d",&command) == 0)//?
		{
			fgets(clear, N, stdin);
			continue;
		}
		switch(command)
		{
		case 1:
			printf("add\n");
			result = client_addusr(socketfd, &msg);
			if (result == SUCCESS)
			{
				puts("添加用户成功");
			}
			else if(result == FAILED )
			{
				printf("%s\n", msg.data);
				puts("添加用户失败");
				continue;
			}
			break;
		case 2:
			printf("delete\n");
			result = client_delete(socketfd, &msg);
			if (result == SUCCESS)
			{
				puts("删除用户成功");
			}
			else if(result == FAILED )
			{
				printf("%s\n", msg.data);
				puts("删除用户失败");
				continue;
			}
			break;
		case 5:
			msg.type = QUIT;
			send(socketfd, &msg, sizeof(MSG), 0);
			goto Exit;
		}
#endif
	}
Exit:
	close(socketfd);
	return 0;
}

int client_addusr(int socketfd,MSG *msg)
{
	printf("请输入用户名->");
	getchar();
	fgets((msg->info).name, N, stdin);
	(msg->info).name[strlen((msg->info).name) - 1] = '\0';

	printf("请输入用户密码->");
	getchar();
	fgets(msg->password, N, stdin);
	msg->password[strlen((msg->password)) - 1] = '\0';

	printf("请输入用户地址->");
	getchar();
	fgets((msg->info).addr, N, stdin);
	(msg->info).addr[strlen((msg->info).addr) - 1] = '\0';

	char clear[N];

input_age:
	printf("请输入用户年龄->");
	if (scanf("%d", &(msg->info).age) == 0)
	{
		printf("输入类型错误\n");
		fgets(clear, N, stdin);
		goto input_age;
	}
	getchar();
	
	msg->type = ADD;
	send(socketfd, msg, sizeof(MSG), 0);
	recv(socketfd, msg, sizeof(MSG), 0);

	return msg->sign;
}
int client_delete(socketfd, &msg)
{
	
	return 0;
}

