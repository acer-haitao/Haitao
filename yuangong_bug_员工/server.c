#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <signal.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  N  128
#define  DATABASE "my.db"
#define  ADD 1
#define  SEARCH 3
typedef struct 
{
	int type;
	char name[N];
	char password[256];   // password or word
} USER;

typedef struct
{
	char name[N];
	char addr[N];
	char age;
	int level;
	int no;
	char phone[64];
	double salary;
} INFO;

int do_login(int connectfd, USER *usr, sqlite3 *db);
int server_ops(int connectfd, USER *usr, sqlite3 *db);
int server_ops_add(int connectfd, INFO *info, sqlite3 *db);
int server_ops_search(int connectfd, INFO *info, sqlite3 *db);

int main(int argc, char *argv[])
{
	printf("你好-->世界\n");
	int listenfd, connectfd;
	struct sockaddr_in server_addr, client_addr;
	pid_t pid;
	sqlite3 *db;
	char *errmsg;
	USER usr;

	if (argc < 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(-1);
	}

	if (sqlite3_open(DATABASE, &db) != SQLITE_OK)//打开数据库 没有则创建
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);
	}

	if(sqlite3_exec(db,"create table usr(name char primary key, password char);", NULL,
				NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}
	else
	{
		printf("create table usr sucess\n");
	}
	if(sqlite3_exec(db, "create table info(name char, addr char, age int, level int, no int, phone char, salary double);", NULL, 
				NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}
	else
	{
		printf("create table info sucess\n");
	}

	if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}
	if (listen(listenfd, 5) < 0)
	{
		perror("fail to listen");
		exit(-1);
	}
	signal(SIGCHLD, SIG_IGN);// 避免僵尸进程
	while (1)
	{
		if ((connectfd = accept(listenfd, NULL, NULL)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}
		if ((pid = fork()) < 0)
		{
			perror("fail to fork");
			exit(-1);
		}
		if (pid == 0)
		{
			do_login(connectfd, &usr, db);
			printf("IP:%s 端口:%d 退出连接....\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			exit(0);
		}
		
		close(connectfd);
	}
	return 0;
}

int do_login(int connectfd, USER *usr, sqlite3 *db)
{	
	char sql[128] = {0};
	char **result;
	int nrow = 0;
	int ncolumn = 0;
	char *errmsg;
	INFO info;

	while((recv(connectfd, usr, sizeof(USER), 0)) > 0 )
	{
		//从数据库里查询姓名和密码
		printf("recv name->%s password->%s\n", usr->name, usr->password);
#if 1 
		sprintf(sql,"select *from usr where name = '%s' and password = '%s';", usr->name, usr->password);
		if(sqlite3_get_table(db, sql, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
		{
			printf("get_table:%s\n",errmsg);
		}
		if(nrow == 0)
		{
			strcpy(usr->password, "请检查用户姓名密码是否正确\n");
		}
		else
		{
			strcpy(usr->password, "成功登录");
			printf("%s login sucess\n", usr->name);
			server_ops(connectfd, usr, db);
		}
		send(connectfd, usr, sizeof(USER), 0);

#endif
	}

	return 0;
}
int server_ops(int connectfd, USER *usr, sqlite3 *db)
{	
	INFO info;
	if(strcmp(usr->name, "zhangsan") == 0)
	{
		usr->type = 88;
		send(connectfd, usr, sizeof(USER), 0);
		printf("管理员 \n");
		recv(connectfd, usr, sizeof(USER), 0);

		switch(usr->type)
		{
		case ADD:
			printf("add \n");
			server_ops_add(connectfd, &info, db);
			break;
		case SEARCH:
			printf("search \n");
			server_ops_search(connectfd, &info, db);
			break;
		}
	}
	else
	{
		printf("普通用户\n");
	}
}
int server_ops_add(int connectfd, INFO *info, sqlite3 *db)
{
	while(recv(connectfd, info, sizeof(INFO), 0) > 0)
	{
		char sql[128] = {0};
		char buf[128] = {0};
		char *errmsg;

		sprintf(sql, "insert into info values('%s', '%s', '%d','%d','%d', '%s','%lf');",
				info->name, info->addr, info->age, info->level, info->no, info->phone,
				info->salary);
		if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
		{
			printf("insert faled \n");
		}
		else
		{
			sprintf(buf, "add sucess");
			printf("%s\n",buf);
		}
	}
	return 0;
}
int server_ops_search(int connectfd, INFO *info, sqlite3 *db)
{
	char sql[128], *errmsg;
	sprintf(sql,"select *from info;");
#if 0
	if(sqlite3_exec(db, sql, do_handler, (void *)&connectfd, &errmsg) != SQLITE_OK)
	{
		printf("seach handler faled\n");
		sqlite3_free(errmsg);
	}
#endif
#if 1
	char **dbresult;
	int nrow, ncolumn;
	int i, j, index;
	char buf[128];
	if(sqlite3_get_table(db, sql, &dbresult, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("get_table faled\n");
	}
	else
	{
		index = ncolumn;
		printf("查到%d条记录\n", nrow);
		for(i = 0; i < nrow; i++)
		{
			printf("第%d条记录\n", i + 1);
			sprintf(buf,"第%d条记录\n", i + 1);
			send(connectfd, buf, sizeof(buf), 0);

			for(j = 0; j < ncolumn; j++)
			{
				printf("字段名:%s 字段值:%s\n", dbresult[j], dbresult[index]);

				sprintf(buf, "字段名:%s 字段值:%s", dbresult[j], dbresult[index]);
				++index;
				send(connectfd, buf, sizeof(buf), 0);
			}
			puts("-------------");
		}
		strcpy(buf, "recv sucess");
		send(connectfd, buf, sizeof(buf), 0);
	}
	//close(connectfd);
#endif
	return 0;
}
#if 0
int do_handler(void *arg, int f_num, char **f_value, char **f_name)
{
	int connectfd;
	INFO info;
	connectfd = *(int *)arg;

}
#endif
