/*************************************************************************
    > File Name: chartoint.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Thu 07 Jul 2016 07:41:59 PM CST
 ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
	char *str = "123";
	int sum = 0;
#if 0
	while(*str != '\0')/* str指向首地址 */
	{
		sum = sum * 10 + *str - '0'; 
		str ++;
	}

	printf("sum = %d\n", sum);
#endif
	while(*str)
		sum = sum * 10 + *str++ - '0';
	printf("sum = %d\n", sum);
	return 0;
}
