/*************************************************************************
    > File Name: sec.c
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 26 Jul 2016 03:06:55 PM CST
 ************************************************************************/

#include <stdio.h>
#include <time.h>

int Nextsecond(int *nyear, int *nmonth, int *ndate, int *nhour, int *nminute, int *nsecond)
{
	/* 把传入的日期秒加1 */
	int ndays = 0;

	(*nsecond)++;
	if (*nsecond >= 60)/* 大于60秒 秒置0 分钟加1*/
	{
		*nsecond = 0;
		(*nminute)++;
		if (*nminute >= 60)/*分钟大于60 小时加1 */
		{
			*nminute = 0;
			(*nhour)++;
			if (*nhour >= 24)/*大于24小时 天加1 */
			{
				*nhour = 0;
				(*ndate)++;
				ndays = GetMonthday(*nyear, *nmonth);/*把每月的天数甩出来*/
				if ((*ndate > ndays) && (ndays > 0))/* 如果大于31或者30 月加1 */
				{
					*ndate = 1;
					(*nmonth)++;
						if (*nmonth > 12)/* 如果月大于12 年加1*/
						{
							*nmonth = 1;
							(*nyear)++;
						}
				}
			}
		}
	}
	return 0;
}

int GetMonthday(int nyear, int nmonth)
{
	int ndays = -1;//?
	if (nmonth >= 1 && nmonth <= 12)
	{
		switch(nmonth)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				ndays = 31;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				ndays = 30;
				break;
			case 2:/* 闰年29 平年28*/
				if (isleapyear(nyear))
				{
					ndays = 29;
				}
				else
				{
					ndays = 28;
				}
		}
	}
	return ndays;
}
int isleapyear(int nyear)
{
	if (nyear < 0)
	{
		nyear = -nyear;
	}
	return ((nyear % 400 == 0) || (nyear % 4 == 0 && nyear % 100 != 0)) ? 1 : 0;
	/* 闰年：1能被400整除 2 能被4整除但是不能被100整除 */
}

int main(int argc, char *argv[])
{	
	time_t Nowtime;
	Nowtime = time(NULL);
	struct tm *TimeInfo;
	TimeInfo = localtime(&Nowtime);
	/*输出当前时间*/
	int nyear = TimeInfo->tm_year + 1900;
	int nmonth = TimeInfo->tm_mon + 1;
	int ndate = TimeInfo->tm_mday;
	int nhour = TimeInfo->tm_hour;
	int nminute = TimeInfo->tm_min;
	int nsecond = TimeInfo->tm_sec;

	printf("当前时间：%d年%d月%d日--%d时%d分%d秒\n", nyear, nmonth, ndate, nhour, nminute, nsecond);

	Nextsecond(&nyear, &nmonth, &ndate, &nhour, &nminute, &nsecond);

	printf("下一秒：%d年%d月%d日--%d时%d分%d秒\n", nyear, nmonth, ndate, nhour, nminute, nsecond);
	/*以上是获取系统时间*/

	printf("请输入 年-月-日-十-分-秒\n");
	scanf("%d-%d-%d-%d-%d-%d", &nyear, &nmonth, &ndate, &nhour, &nminute, &nsecond);
	Nextsecond(&nyear, &nmonth, &ndate, &nhour, &nminute, &nsecond);
	printf("下一秒：%d年%d月%d日--%d时%d分%d秒\n", nyear, nmonth, ndate, nhour, nminute, nsecond);
	/*手动输入时间*/

	return 0;
}
