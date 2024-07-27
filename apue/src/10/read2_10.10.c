#include "apue.h"
#include <setjmp.h>

static void		sig_alrm(int);
static jmp_buf	env_alrm;

/*
	实例10-11:使用longjmp，带时间限制调用read
	来达到一个无需担心的慢速系统调用是否被中断
*/ 
int main(void) {
	int		n;
	char	line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");
	//标志
	if (setjmp(env_alrm) != 0)
		//longjmp回来后就退出了
		err_quit("read timeout");

	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void sig_alrm(int signo) {
	//触发信号后就跳回到setjmp处，执行中断逻辑
	longjmp(env_alrm, 1);
}
