#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//图6-11:使用本章中的函数，特别是strftime打印包含当前日期和时间的字符串
int main(void) {
	time_t t;
	struct tm *tmp;
	char buf1[16];
	char buf2[64];
	//取日历时间放到t中
	time(&t);
	//日历时间(time_t)转换为分解的本地时间(tm)
	tmp = localtime(&t);
	/*
		对分解时间进行格式化:16个字节的缓冲区(不够)
		%r:本地时间(12小时制)
		%a:缩写的周日名(星期几)
		%b:缩写的月名(英文简称,例如January就是Jan)
		%d:月日(1-31)
		%Y:年
	*/
	if (strftime(buf1, 16, 
			"time and date: %r, %a %b %d, %Y", 
			tmp) == 0)
		printf("buffer length 16 is too small\n");
	else
		printf("%s\n", buf1);
	//使用64个字节的缓冲区(够了)	
	if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)
		printf("buffer length 64 is too small\n");
	else
		//04:34:31 PM, Fri Jul 12, 2024
		printf("%s\n", buf2);
	exit(0);
}
