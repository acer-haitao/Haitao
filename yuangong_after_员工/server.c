#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N      64
#define READ   1   //查询用户信息
#define CHANGE 2   //修改用户信息
#define DELETE 3   //删除用户
#define ADD    4   //添加用户
#define LOAD   5   //用户申请登录
#define QUIT   6   //用户退出时发给服务器的通知消息
#define SUCCESS  7 //服务器操作成

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
int     Info_rmark = 0;//文件Info.text互斥操作的读
int     Info_wmark = 0;//文件Info.text互斥操作的写
int     User_rmark = 0;//文件User.text互斥操作的读
int     User_wmark = 0;//文件User.text互斥操作的写

void findUser(MSG *msg);
void findUser(MSG *msg);
void *pthread_function(void *arg);
int server_addusr(MSG *msg);
int getMsg(int connectfd, MSG *msg);

int main(int argc, char *argv[])
{
	printf("你好<--服务端-->世界\n");
#if 1
	USER usr;
	strcpy(usr.name, "haitao");
	strcpy(usr.password, "1");
	usr.type = 11;
	usr.no = 100;

	FILE *fp = fopen("./user.txt","wb");
	fwrite(&(usr), sizeof(USER), 1, fp);
	fclose(fp);

#endif 
	int listenfd, connectfd;
	struct sockaddr_in server_addr, client_addr;

	if (argc < 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(-1);
	}
	printf("listen\n");
	if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));
	printf("bind\n");
	if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}
	printf("listen\n");
	if (listen(listenfd, 5) < 0)
	{
		perror("fail to listen");
		exit(-1);
	}
	printf("while\n");
	while (1)
	{
		printf("accept\n");
		if ((connectfd = accept(listenfd, NULL, NULL)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}
		printf("客户-->IP地址%s 端口号:%d连接成功\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		pthread_t child_pthread;
		/*1线程标识符 2设置属性 3要执行函数名 4传入函数的参数*/
		printf("pthread_create\n");
		if(pthread_create(&child_pthread, NULL, pthread_function, (void *)connectfd) < 0)
		{
			printf("pthread_create failed\n");
			exit(-1);
		}
		printf("pthread_create_after\n");
	}
	close(listenfd);//?
	return 0;
}
void *pthread_function(void *arg)
{
	printf("pthread_function_doing\n");
	int connectfd;
	connectfd = (int)arg;
	MSG msg;
	int n;
	while(1)
	{
		n = recv(connectfd, &msg, sizeof(MSG), 0);
		if(msg.type == QUIT)
		{
			printf("客户:%s 退出！\n",msg.name);
			pthread_exit(NULL);
			close(connectfd);
		}
		if(n == -1) break;
		getMsg(connectfd, &msg);//给结构体地址 操作结构体内容
		send(connectfd, &msg, sizeof(MSG), 0);//这句话如果不注释 客户端Ctrl+C 服务端也挂掉
		printf("pthread_function_while\n");
	}
	close(connectfd);
	pthread_exit(NULL);
}
int getMsg(int connectfd, MSG *msg)
{

	switch(msg->type)
	{
	case LOAD :
		findUser(msg);
		break;
	case ADD:
		server_addusr(msg);
	default:
		break;
	}
	//send(connectfd, &msg, sizeof(MSG), 0);
	return 0;
}
void findUser(MSG *msg)
{	
	FILE *fp;
	int flag = 0;
	while(User_wmark > 0)//?
	{
		usleep(100000);
	}
	User_rmark++;

	if((fp = fopen("./user.txt", "rb")) == NULL)//打开只读
	{
		printf("用户%s 的请求失败\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data, "没有数据文件\n");
		return;
	}

	USER usr_temp;
	/*从fp中读取一条(结构体大小de)记录放入&处缓存*/
	while(fread(&usr_temp, sizeof(USER), 1, fp) != 0)
	{
		if(strcmp(usr_temp.name, msg->name) == 0)
		{
			if((strcmp(msg->password, usr_temp.password)) == 0)
			{
				flag = 1;//?
				msg->sign = SUCCESS;
				msg->info.type = usr_temp.type;
				strcpy(msg->data, "登录成功\n");
				return;
			}
		}
		if(flag == 0)
		{
			msg->sign = FAILED;
			strcpy(msg->data, "登录失败!\n");
			return;
		}
	}
	printf("1++++++++++++\n");
	fclose(fp);
	User_rmark--;//?
}
int server_addusr(MSG *msg)
{
	FILE *fp;
	USER usr;
	strcpy(usr.name, msg->info.name);
	strcpy(usr.password, msg->password);
	usr.type = STAFF;
	usr.no = msg->info.no;

	while((User_wmark > 0) && (User_rmark > 0))//?
	{
		usleep(1000000);
	}
	User_wmark++;

	if ((fp = fopen("./user.txt", "ab")) == NULL)
	{
		printf("用户%s请求打开数据文件失败\n", msg->name);
		msg->sign = FAILED;
		strcpy(msg->data, "没有数据文件");
		return;
	}
	fwrite(&(usr), sizeof(USER), 1, fp);
	printf("用户:%s添加成功\n", msg->name);

	msg->sign = SUCCESS;
	strcpy(msg->data, "添加用户成功");

	fclose(fp);
	User_wmark--;
	return 0;
}

