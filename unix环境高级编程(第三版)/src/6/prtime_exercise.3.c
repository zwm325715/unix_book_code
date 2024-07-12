#include "apue.h"
#include <time.h>
//习题3
int main(void) {
	time_t		caltime;
	struct tm	*tm;
	char		line[MAXLINE];
	//取日历时间
	if ((caltime = time(NULL)) == -1)
		err_sys("time error");
	//转换成分解时间
	if ((tm = localtime(&caltime)) == NULL)
		err_sys("localtime error");
	/*
		格式化输出放到line中
		%a:缩写的周日名(星期几)
		%b:缩写的月名(英文简称,例如January就是Jan)
		%d:月日(1-31)
		%X:本地时间(21:24:52)
		%Z:时区名
		%Y:年
	*/
	if (strftime(line, MAXLINE, "%a %b %d %X %Z %Y\n", tm) == 0)
		err_sys("strftime error");
	fputs(line, stdout);
	exit(0);
}
