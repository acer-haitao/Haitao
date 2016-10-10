/*************************************************************************
    > File Name: c_mysql_test.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 23 Sep 2016 08:13:21 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define N 1024
void error_quit(const char *str, MYSQL *connect)
{
	fprintf(stderr, "%s:%d:%s\n",str, mysql_errno(connect), mysql_error(connect));
	if(connect != NULL)
	{
		mysql_close(connect);
	}
	return;
}

int main(int argc, char *argv[])
{
	printf("hello world\n");
	MYSQL *my_con = malloc(sizeof(MYSQL));//申请空间
	MYSQL_RES *my_res;
	MYSQL_FIELD *my_field;
	MYSQL_ROW my_row;
	int rows, i;
	int res;
	char sql[N] = {0};

	/* 连接数据库 */
	mysql_init(my_con);
	my_con = mysql_real_connect(my_con, "localhost","root","haitao","mytest",0,NULL,0);
	/*
	 * 上面描述了五个参数的主要取值，MYSQL
	 * 为mysql_init函数返回的指针，host为null或 
	 * localhost时链接的是本地的计算机，当mysql默认安装在unix（或类unix）系统中，root账户是没//
	 * 有密码的，因此用户名使用root，密码为null，当db为空的时候，函数链接到默认数据库，在进行
	 * mysql安装时会存在默认的test数据库，因此此处可以使用test数据库名称，port端口为0，使用
	 * unix连接方式，unix_socket为null时，表明不使用socket或管道机制，最后一个参数经常设置为0
	 */
	if(my_con == NULL)
	{
		error_quit("连接失败", my_con);
	}
	else
	{
		printf("连接成功\n");
	}
#if 0
	/* 创建表*/
	sprintf(sql,"%s","create table class2(name varchar(100), age int, birthday DATE);");
	res = mysql_query(my_con,sql);
	if (res != 0)
	{
		error_quit("create table",my_con);
	}
	else
	{
		printf("创建表成功\n");
	}
#endif
	/* 向数据库里插入一条数据 */
	sprintf(sql,"%s","insert into class2(name, age, birthday) value('四',27,NOW());");
	res = mysql_query(my_con, sql);
	if (res != 0)
	{
		error_quit("insert into failed-->", my_con);
	}

	/* 返回表中被影响的行数 */
	res = mysql_affected_rows(my_con);
	printf("插入的是第%d行\n",res);

	/* 获取整个表的内容 */
	sprintf(sql,"%s","select *from class2;");
	res = mysql_query(my_con, sql);
	if (res != 0)
	{
		error_quit("select failed", my_con);
	}
	my_res = mysql_store_result(my_con);
	if (NULL == my_res)
	{
		error_quit("get result failed", my_con);
	}
	
	/* 获取列表的列数 */
	rows = mysql_num_fields(my_res);
	/* 获取并输出表头 */
	my_field = mysql_fetch_fields(my_res);
	for (i = 0; i < rows; i++)
	{
		printf("%s\t",my_field[i].name);
	}
	printf("\n----------------------------------\n");	

	/* 输出整个表的内容 */
	while(1)
	{
		my_row = mysql_fetch_row(my_res);//返回一个数组值，当前行数据信息
		if (NULL == my_row)
		{
			//printf("mysql_fetch_row\n");
			break;//到空行是跳出结束
		}
		for (i = 0; i < rows; i++)//打印当前行每一列的值
		{
			if (NULL == my_row[i])
			{
				printf("NULL\t");
			}
			else
			{
				printf("%s\t", (char *)my_row[i]);
			}
		}
		putchar(10);
	}

	/* 释放空间 关闭连接 */
	mysql_free_result(my_res);
	mysql_close(my_con);
	free(my_con);

	return 0;
}

