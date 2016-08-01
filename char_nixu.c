/*************************************************************************
    > File Name: char_nixu.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Sat 02 Jul 2016 11:43:35 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char buf1[] = "abcdefg";
	int len = strlen(buf1);
	printf("strlen = %d sizeof =%d\n",len, sizeof(buf1));

	char *pfirst = buf1;
	char *plast = buf1 + len -1;
	char c;

	while(pfirst < plast)
	{
		c = *pfirst;/* 保存第一个字符 */
		*pfirst = *plast;/*把最后一个给第一个 */
		*plast = c;
		++pfirst;
		--plast;
	}
	printf("%s\n",buf1);
	return 0;
}
