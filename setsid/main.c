/*************************************************************************
    > File Name: main.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 03 Sep 2016 04:07:11 PM CST
 ************************************************************************/

#include <stdio.h>
#include <time.h>

void init_daemon(void);

int main(int argc, char *argv[])
{
	FILE *fp;
	time_t t;

	init_daemon();
	while(1) 
	{
		printf("hello world\n");
		sleep(1);
		if ((fp = fopen("test.log", "a")) != NULL)
		{
			t = time(0);
			fprintf(fp, "I  am here %s", asctime(localtime(&t)));
			fclose(fp);
		}
	}

	return 0;
}
