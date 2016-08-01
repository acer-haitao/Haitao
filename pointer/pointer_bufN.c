/*************************************************************************
    > File Name: pointer_bufN.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Fri 17 Jun 2016 07:38:17 PM PDT
 ************************************************************************/

#include <stdio.h>
int main(int argc, const char *argv[])
{
	int i = 0;
	int array[20] = {0};
	int *ptr = array;
	for(i = 0; i < 20; i++)
	{
		(*ptr)++;
		ptr++;
		printf("%d\t", array[20]);
	
	}
		
	putchar(10);
	printf("char = %d\n",sizeof(char));
		printf("int = %d\n",sizeof(int));
		printf("char * = %d\n",sizeof(char *));
		printf("int * = %d\n",sizeof(int *));

	return 0;
}
