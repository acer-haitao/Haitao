/*************************************************************************
    > File Name: c_sql_connect.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sun 09 Oct 2016 04:20:48 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>

#define N 100

typedef struct {
	char name[N];
	int age;
	char class[N];
	char addr[N];
}stu;

int main(int argc, char *argv[])
{
	MYSQL mysql,*connect;
	stu stu_test;
	char SQL[1024] = {0};

	mysql_init(&mysql);//初始化 (初始化一个socket的TCP连接)
	connect = mysql_real_connect(&mysql,"localhost","root","haitao","mytest",0,0,0);
	if (connect == NULL)
	{
		printf("链接数据库失败-->%s\n",mysql_error(&mysql));
	}
	else
	{
		printf("链接数据库成功\n");
	}
	
	if ((mysql_query(connect, "set names utf8;")) != 0)//设置字符集
	{
		printf("set names :%s\n",mysql_error(&mysql));
		return -1;
	}
	else
	{
		printf("设置字符集成功\n");
	}
	
	if ((mysql_query(connect,"create table stu1(name varchar(100), age int, class varchar(100), addr varchar(100));")) != 0)
	{
		printf("Created :%s\n",mysql_error(&mysql));
	}
	else
	{
		printf("创建表成功\n");
	}
#if 1 //插入数据
	puts("请输入要插入的姓名,年龄,班级,地址--> 张三,19,C++,北京海淀");
	scanf("%s%d%s%s",stu_test.name, &stu_test.age, stu_test.class, stu_test.addr);
	printf("%s-%d-%s-%s\n",stu_test.name, stu_test.age, stu_test.class, stu_test.addr);

	sprintf(SQL,"insert into stu1 values('%s',%d,'%s','%s');",stu_test.name, stu_test.age, stu_test.class, stu_test.addr);
	printf("SQL-->%s\n",SQL);

#if 0
	printf("您输入的是%s\n",stu_test.name);
	printf("您输入的是%s\n",stu_test.addr);
	printf("您输入的是%s\n",stu_test.class);
	printf("您输入的是%d\n",stu_test.age);
#endif
	if (mysql_query(connect, SQL) != 0)
	{
		printf("insert :%s\n",mysql_error(&mysql));
	}
#endif

#if 1 //实现输入删除语句和read/wite写屏处理 printf遇换行或缓冲区满输出
	memset(SQL, 0, sizeof(SQL));
	sprintf(SQL, "请输入要删除的姓名>");
	write(STDOUT_FILENO, SQL, strlen(SQL));//想屏幕输出
	memset(stu_test.name, 0, sizeof(stu_test.name));
	read(STDIN_FILENO, stu_test.name, sizeof(stu_test.name));//从屏幕输入
	stu_test.name[strlen(stu_test.name) - 1] = 0;//解决最后换行符问题
	
	memset(SQL, 0, sizeof(SQL));
	sprintf(SQL, "delete from stu1 where name = '%s';",stu_test.name);
	printf("%s\n",SQL);

	if (mysql_query(connect, SQL) != 0)
	{
		printf("delete error:%s\n",mysql_error(&mysql));
	}
	else
	{
		printf("delete %s sucess\n",stu_test.name);
	}
#endif

	mysql_close(connect);
	return 0;
}
