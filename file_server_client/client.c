/*************************************************************************
  > File Name: client.c
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Sat 11 Jun 2016 02:05:04 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#define N 128
#define err_log(errlog) do{perror(errlog);exit(1);}while(0)

int client_getlist(struct sockaddr_in serveraddr);
int client_getdown(char *p, struct sockaddr_in serveraddr);
int client_connect(int sockfd, struct sockaddr_in serveraddr);
int client_put(char *p, struct sockaddr_in serveraddr);
void client_help(void);


int main(int argc, const char *argv[])
{
	char buf[N] = {0};
	struct sockaddr_in serveraddr;

	if(argc < 3)
	{
		printf("请按照正确的格式(%s 192.168.1.158 10000)输入：\n",argv[0]);
		return -1;
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));
	while(1)
	{
		printf("请输入你的选择：getlist,getdown,putfile,help,quit\n");
		fgets(buf, N, stdin);
		buf[strlen(buf) - 1] = '\0';
		if(strncmp(buf, "getlist", 7) == 0)
		{
			client_getlist(serveraddr);
		}
		else if(strncmp(buf, "getdown", 7) == 0)
		{
			client_getdown(buf, serveraddr);
		}
		else if(strncmp(buf, "put", 3) == 0)
		{
			client_put(buf, serveraddr);
		}
		else if(strncmp(buf, "help", 4) == 0)
		{
			client_help();
		}
		else if(strncmp(buf, "quit", 4) == 0)
		{
			printf("正在退出.....\n");
			return -1;
		}
		else
		{
			printf("请按照正确的格式输入：\n");
		}
	}
	return 0;
}

int client_getlist(struct sockaddr_in serveraddr)
{
	char buf1[N] = {0};
	int sockfd = 0;


	sockfd = client_connect(sockfd, serveraddr);

	strcpy(buf1, "L");
	send(sockfd, buf1, N, 0);//客户端通过sockfd发送

	while((recv(sockfd, buf1, N, 0)) > 0)//通过sockfd接收
	{
		printf("%s\t\t",buf1);
	}
	printf("获取服务器端文件目录如上：\n");
	
	close(sockfd);
	return 0;
}

int client_getdown(char *p, struct sockaddr_in serveraddr)
{
	int sockfd = 0;
	char buf[N] = {0};
	int fd = 0;
	int nbyte = 0;

	sockfd = client_connect(sockfd, serveraddr);

	sprintf(buf, "G%s", p + 8);
	send(sockfd, buf, N, 0);
	printf("++++++++++++++\n");

	recv(sockfd, buf, N, 0);
	printf("recv = %c\n",buf[0]);
	if (strncmp(buf, "Y", 1) == 0)
	{
		if((fd = open(p + 8, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
		{
			err_log("创建本地接收文件失败\n");
		}
		while((nbyte = recv(sockfd, buf, N, 0)))
		{
			printf("%s",buf);
			write(fd, buf, nbyte);
		}
		printf("下载服务端文件:%s成功\n", p + 8);
	}
	else
	{
		printf("服务端没有您要下载的文件:%s\n",p + 8);
		return -1;
	}

	close(sockfd);
	close(fd);
	return 0;
}

int client_put(char *p, struct sockaddr_in serveraddr)
{
	int fd = 0;
	int sockfd = 0;
	char buf1[N] = {0};
	int nbyte = 0;
	
	printf("put->%s\n",p +4);
	if((fd = open(p + 4,O_RDONLY)) < 0)
	{
		err_log("打开要上传的失败");
	}

	sockfd = client_connect(sockfd, serveraddr);
	
	sprintf(buf1, "P%s", p + 4);
	send(sockfd, buf1, N, 0);

	while((nbyte = read(fd, buf1, N)) > 0)
	{
		send(sockfd, buf1, nbyte, 0);
	}
	printf("向服务端传送%s成功\n",p + 4);
	
	close(sockfd);
	close(fd);

	return 0;
}

int client_connect(int sockfd, struct sockaddr_in serveraddr)
{
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		err_log("创建套接字失败:");
	}
	if((connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0)
	{
		err_log("连接失败:");
	}	
	return sockfd;
}
void client_help(void)
{
	printf("+++++++++++++++++++++++++++++++++++++\n");
	printf("请输入你的选择：\n");
	printf("1 getlist 获取文件列表\n");
	printf("2 put 1.c 上传文件至服务端\n");
	printf("3 getdown 1.c下载服务端文件\n");
	printf("4 quit 退出 help 帮助\n");
	printf("+++++++++++++++++++++++++++++++++++++\n");
	return;
}

