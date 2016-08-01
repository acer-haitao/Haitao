/*************************************************************************
  > File Name: server.c
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


int server_list(int connectfd);
int	server_down(int connectfd, char *p);
int server_put(int connectfd, char *p);

int main(int argc, const char *argv[])
{
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	int sockfd = 0;
	int connectfd = 0;
	char buf1[N] = {0};

	socklen_t addrlen = sizeof(struct sockaddr);

	if(argc < 3)
	{
		printf("请按照正确的格式(%s 192.168.1.158 10000)输入：\n",argv[0]);
		return -1;
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		err_log("创建套接字失败:");
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	if((bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0)
	{
		err_log("绑定套接字失败:");
	}
	if((listen(sockfd, 5)) < 0)
	{
		err_log("监听失败:");
	}

	while(1)
	{
		printf("等待客户连接...\n");
		if((connectfd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen)) < 0)
		{
			err_log("接收客户连接失败");
		}
		printf("客户端：%s 端口号:%d 连接成功\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

		recv(connectfd, buf1, N, 0);
		printf("recv = %s\n",buf1);

		switch(buf1[0])
		{
		case 'L':
			server_list(connectfd);
			break;
		case 'G':
			server_down(connectfd, buf1);
			break;
		case 'P':
			server_put(connectfd, buf1);
			break;
		default:
			printf("客户端输入的%s为无效数据\n",buf1 + 1);
		}
	}

	close(sockfd);
	return 0;
}

int server_list(int connectfd)
{
	DIR *dir = NULL;
	struct dirent *dp;
	char buf[N] = {0};
	if((dir = opendir(".")) == NULL)
	{
		err_log("服务端打开文件目录失败");
	}
	while((dp = readdir(dir)) != NULL)
	{
		if(dp->d_name[0] == '.')
		{
			continue;
		}
		strcpy(buf, dp->d_name);
		printf("%s\t \t",buf);
		send(connectfd, buf, N, 0);
		usleep(50);
	}
	printf("向客户端传送列表完成\n");
	closedir(dir);
	close(connectfd);

	return 0;
}

int	server_down(int connectfd, char *p)
{
	int fd = 0;
	char  buf[N] = {0};
	int nbyte = 0;

	if((fd = open(p+1, O_RDONLY)) < 0)
	{
		strcpy(buf, "N");
		send(connectfd, buf, N, 0);
		printf("打开文件失败\n");
	}
	else
	{
		strcpy(buf, "Y");
		send(connectfd, buf, N, 0);
		printf("客户端正在下载%s\n",p+1);
		while((nbyte = read(fd, buf, N)))
		{
			//printf("%s",buf);//最后为什么会多发一小段？但没被写入
			send(connectfd, buf, nbyte, 0);
			usleep(50);
		}
		printf("向客户端发送文件成功\n");
	}
	close(fd);
	close(connectfd);
	return 0;
}
int server_put(int connectfd, char *p)
{
	int fd = 0;
	int nbyte = 0;
	char buf1[N] = {0};

	/* O_CREAT文件不存在创建  O_TRUNC 文件已存在删除原有数据 O_APPEND
	 * 文件已存在尾部追加 O_EXCL 文件已存在 返回错误信息 
	 *  S_IRUSR | S_IWUSR <=> 0600文件所有者可读可写 */
	if((fd = open(p + 1, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR)) < 0)
	{
		err_log("打开服务端本地文件失败\n");
	}
	while((nbyte = recv(connectfd, buf1, N, 0)) > 0)
	{
		write(fd, buf1, nbyte);
	}
	printf("接收客户端文件:%s成功\n", p + 1);
	close(fd);
	close(connectfd);
	return 0;
}

