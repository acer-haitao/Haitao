#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  N  128 
#define  ADD 1
#define  SEARCH 3

typedef struct 
{
	int type;
	char name[N];
	char password[256];   // password or word or remark
} USER;
typedef struct
{
	char name[N];
	char addr[N];
	int  age;
	int level;
	int no;
	char phone[64];
	double salary;
} INFO;


int do_login(int socketfd, USER *usr);
int client_ops(int socketfd, USER *usr);
int client_addusr(int socketfd, USER *usr, INFO *info);
int client_search(int socketfd, USER *usr, INFO *info);


int main(int argc, char *argv[])
{
	printf("你好<--世界\n");
	int socketfd ;
	struct sockaddr_in server_addr;
	USER usr;
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
	do_login(socketfd, &usr);
}
int do_login(int socketfd, USER *usr)
{
	char buf[N] = {0};
	while(1)
	{
		printf("************************************\n");
		printf("   *    请输入用户名和密码    *\n");
		printf("************************************\n");

		printf("input your name:");
		scanf("%s", usr->name);
		printf("input your password:");
		scanf("%s", usr->password);
		send(socketfd, usr, sizeof(USER), 0);
		recv(socketfd, usr, sizeof(USER), 0);
		printf("%s \n",usr->password);
		if((strcmp(usr->password, "成功登录") == 0))
		{
			client_ops(socketfd, usr);
			continue;
		}
	}
		return 0;
}
int client_ops(int socketfd, USER *usr)
{
	INFO info;
	
	if((usr->type == 88))
	{
		
		printf("管理员\n");	
		printf("*****************************************\n");
		printf(" 1增加用户 2删除用户 3查询 4修改 5退出  *\n");
		printf("*****************************************\n");
		int n;
		scanf("%d",&n);
		switch(n)
		{
		case 1 :
			client_addusr(socketfd, usr, &info);
			break;
		case 2 :
			break;
		case 3 :
			client_search(socketfd, usr, &info);
			break;
		case 4 :
			break;
		case 5 :
			break;
		default:
			printf("请检查您的输入是否有误！\n");
		}

		}
	
	
	else
	{
		printf("普通用户\n");
		printf("************************************\n");
		printf("    1查询 2修改密码 3退出*\n");
		printf("************************************\n");
		int n;
		scanf("%d",&n);
		switch(n)
		{
		case 1 :
			break;
		case 2 :
			break;
		case 3 :
			break;
		default:
			printf("请检查您的输入是否有误！\n");
		}
	}
	
	
	return 0;
}
int client_addusr(int socketfd, USER *usr, INFO *info)
{
	usr->type = ADD;
	puts("请输入姓名：");
	scanf("%s",info->name);
	puts("请输入地址：");
	scanf("%s",info->addr);
	puts("请输入年龄：");		
	scanf("%d",&info->age);
	puts("请输入等级：");		
	scanf("%d",&info->level);
	puts("请输入编号：");		
	scanf("%d",&info->no);
	puts("请输入电话：");		
	scanf("%s",info->phone);
	puts("请输入工资：");		
	scanf("%lf",&info->salary);
	send(socketfd, usr, sizeof(USER), 0);
	sleep(1);
	send(socketfd, info, sizeof(INFO), 0);
	return 0;
}
int client_search(int socketfd, USER *usr, INFO *info)
{
	usr->type = SEARCH;
	char buf[128];
	send(socketfd, usr, sizeof(USER), 0);
	while((recv(socketfd, buf, sizeof(buf), 0)) > 0)
	{
		if(strcmp(buf, "recv sucess") == 0)
		{
			printf("%s\n",buf);	
			break;
		}	
		printf("%s\n", buf);
	}
	printf("-----------------\n");

	return 0;
}

