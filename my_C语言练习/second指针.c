/*************************************************************************
    > File Name: second指针.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: 2016年08月22日 星期一 21时55分21秒
 ************************************************************************/

#include <stdio.h>

void swap(int *p1, int *p2)
{
	int t;
	int *p;
	t = *p1;
	*p1 = *p2;
	*p2 = t;

	p = p1;
	p1 = p2;
	p2 = p;
}
void swap2(int **m, int **n)
{
	int *p;
	p = *m;
	*m = *n;
	*n = p;
}
int main(int argc, char *argv[])
{
	int a = 1, b = 2;
	int *p = &a, *q = &b;
	swap(p, q);
	printf("%d %d %d %d\n",a, b, *p, *q);
	swap2(&p, &q);
	printf("%d %d %d %d\n",a, b, *p, *q);
	return 0;
}
