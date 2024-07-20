#include "apue.h"

static void	f1(void), f2(void);
//习题8.2:错误使用vfork的例子,运行此程序会产生core文件(发生段错误)
int main(void) {
	f1();
	f2();
	_exit(0);
}

static void f1(void) {
	pid_t	pid;

	if ((pid = vfork()) < 0)
		err_sys("vfork error");
	/* child and parent both return */
}

static void f2(void) {
	/* automatic variables */
	char	buf[1000];		
	int		i;

	for (i = 0; i < sizeof(buf); i++)
		buf[i] = 0;
}
