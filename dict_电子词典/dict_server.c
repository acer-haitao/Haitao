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

#define  N  16
#define  R  1   //  user register
#define  L  2   //  user login
#define  Q  3   //  query word
#define  H  4   //  history record

#define DATABASE "my.db"
char *errmsg;

typedef struct 
{
	int type;
	char name[N];
	char data[256];   // password or word
} MSG;

void do_register(int connectfd, MSG *msg, sqlite3 *db);
void do_login(int connectfd, MSG *msg, sqlite3 *db);
void do_query(int connectfd, MSG *msg, sqlite3 *db);
void do_history(int connectfd, MSG *msg, sqlite3 *db);
void do_client(int connectfd, sqlite3 *db);
void getdate(char data[]);
int do_search(int connectfd, MSG *msg);
int handler_callback(void *arg, int f_num1, char **f_num, char **f_value);

int main(int argc, char *argv[])
{
	printf("你安徽\n");
	int listenfd,connectfd;
	struct sockaddr_in server_addr;
	pid_t pid;
	sqlite3 *db;
	if (argc < 3)
	{
		printf("Usage : %s <serv_ip> <serv_port>\n", argv[0]);
		exit(-1);
	}
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)//打开数据库
	{
		printf("error:%s\n",sqlite3_errmsg(db));
		exit(-1);
	}
	//创建两张表 一张记录用户信息 一张记录查询单词信息
	if(sqlite3_exec(db,"create table dict(name char primary key, data char);", NULL,
				NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}
	else
	{
		printf("create table dict sucess\n");
	}
#if 0
	if(sqlite3_exec(db, "create table record(name char, world char,);", NULL, 
				NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}
	else
	{
		printf("create table record sucess\n");
	}
#endif
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
	while ( 1 )
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
		if (pid == 0)//子进程处理客户操作 父进程accept
		{
			do_client(connectfd, db);
		}
		close(connectfd);
	}
	return 0;
}
void do_client(int connectfd, sqlite3 *db)
{
	MSG msg;//用来接收客户端发来的信息
	while((recv(connectfd, &msg, sizeof(msg), 0)) > 0)
	{
		//printf("%d\n",msg.type);
		switch(msg.type)
		{
		case R:
			do_register(connectfd, &msg, db);
			break;
		case L:
			do_login(connectfd, &msg, db);
			break;
		case Q:
			do_query(connectfd, &msg, db);
			break;
		case H:
			do_history(connectfd, &msg, db);
			break;
		}
	}
	printf("%s quit the connect.....\n",msg.name);
	exit(0);
	return;
}
void do_register(int connectfd, MSG *msg, sqlite3 *db)
{    
	char sql[128] = {0};
	char buf[16] = {0};

	sprintf(sql, "insert into dict values('%s','%s');", msg->name, msg->data);
	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		sprintf(buf, "user %s exists",msg->name);
		send(connectfd, buf, sizeof(buf), 0);
	}
	else
	{
		sprintf(buf, "user %s register sucess", msg->name);
		send(connectfd, buf, sizeof(buf), 0);
		printf("%s\n",buf);
	}
	return;
}
void do_login(int connectfd, MSG *msg, sqlite3 *db)
{    
	char sql[128] = {0};
	char **result;
	int nrow = 0;
	int ncolumn = 0;
	char *errmsg;

	//从数据库里查询姓名和密码
	sprintf(sql,"select *from dict where name = '%s' and data = '%s';", msg->name, msg->data);
	/* nrow查到多少行记录 ncolumn->多少列
	 * result查询结果->第一行字段名后面接每个字段的值 
	 **/
	if(sqlite3_get_table(db, sql, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}
	if(nrow == 0)
	{
		strcpy(msg->data, "login failed");
	}
	else
	{
		strcpy(msg->data, "login sucess");
		printf("%s login sucess\n", msg->name);
	}
	send(connectfd, msg, sizeof(MSG), 0);

	sqlite3_free_table(result);//释放char **查询结果
	sqlite3_close(db);
	return;
}

void do_query(int connectfd, MSG *msg, sqlite3 *db)
{
	/*此功能函数完成：查询/记录两个功能*/
	puts("query");
	char sqlstr[128], *errmsg;
	int found = 0;
	char date[128], word[128];
	strcpy(word, msg->data);
	found =do_search(connectfd, msg);

	if(found)
	{
		getdate(date);
		sprintf(sqlstr, "insert into record values('%s', '%s', '%s')", msg->name, date, word);
		if(sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != SQLITE_OK)
		{
			printf("error : %s\n", errmsg);
		}
	}
	else
	{
		strcpy(msg->data, "not found");
	}
	send(connectfd, msg, sizeof(MSG), 0);
	return;

}

void getdate(char date[])
{	
	time_t t;
	struct tm *tp;
	
	time(&t);
	tp = localtime(&t);

	sprintf(date,"%d-%d-%d %d:%d:%d", tp->tm_year + 1900,
			tp->tm_mon, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
	return;
}
int do_search(int connectfd, MSG *msg)
{    
	FILE *fp;
	char tmp[300] = {0};
	int len, result;
	len = strlen(msg->data);
	char *p;

	if((fp = fopen("dict.txt", "r")) == NULL)
	{
		sprintf(msg->data, "failed to open dict");
		send(connectfd, msg, sizeof(MSG), 0);
	}
	while((fgets(tmp, 300, fp)) != NULL)
	{
		/*字符相等返回0  s1 > s2返回大于0的整数 否则返回小于0的数*/
		result = strncmp(msg->data, tmp, len);
		if(result > 0) continue;
		if(result < 0 || tmp[len] != ' ') break;
		p = tmp + len;
		while(*p == ' ') p++;
		strcpy(msg->data, p);

		fclose(fp);
		return 1;
#if 0
	    if(result < 0) break;
		if((result == 0) && tmp[len] == ' ')//相等且下一个字符为空
		{
			p = tmp + len;
			while(*p == ' ') p++;
			strcpy(msg->data, p);
			printf("%s", p);
			fclose(fp);
			return 1;
		}
#endif
	}

	fclose(fp);
	return 0;
}
#if 1
void do_history(int connectfd, MSG *msg, sqlite3 *db)
{    
	char sql[256] = {0};
	char *errmsg;

	sprintf(sql, "select *from  record where  name = '%s';", msg->name);
	if((sqlite3_exec(db, sql, handler_callback, (void *)&connectfd, &errmsg)) != SQLITE_OK)
	{
		printf("do_history sqlite3_exec :%s\n",errmsg);
		sqlite3_free(errmsg);
	}
	msg->data[0] = '\0';
	send(connectfd, msg, sizeof(MSG), 0);
	return;
}

int handler_callback(void *arg, int f_num1, char **f_num, char **f_value)
{     
	int connectfd;
	MSG msg;
	connectfd = *(int *)arg;
	sprintf(msg.data, "%s %s %s", f_num[0], f_num[0], f_num[2]);
	send(connectfd, &msg, sizeof(MSG), 0);
	return 0;
}
#endif
