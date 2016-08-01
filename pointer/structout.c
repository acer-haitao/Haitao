/*************************************************************************
    > File Name: structout.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 30 Jun 2016 11:28:31 AM CST
 ************************************************************************/

#include <stdio.h>
struct stu{
	int num;
	char name[21];
	char sex;
	float score;
	int age;
};/* 4字节对齐  */
union u{
	int a;
	char s;
	char b[19];
}un;

int main(int argc, char *argv[])
{
	struct stu s = {100, "zhangsan", 'N', 96.5, 18};
	struct stu *p;
	p = &s;

	printf("结构体大小：%d\n",sizeof(s));
	printf("联合体大小：%d\n",sizeof(un));
	printf("num = %d\n", p->num);
	printf("name = %s\n",p->name);
	printf("sex = %c\n",p->sex);
	printf("age = %d\n",p->age);
	printf("score = %f\n",p->score);

	return 0;
}
