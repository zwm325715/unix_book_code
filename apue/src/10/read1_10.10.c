#include "apue.h"
#include <stdio.h>

static void	sig_alrm(int);
//图10-10 带时间限制调用read:从标准输入读一行,然后将其写到标准输出上
int main(void) {
	int		n;
	char	line[MAXLINE];
	//设置SIGALRM的信号hanlder为sig_alrm
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");
	//定时器:10s后产生SIGALRM信号
	alarm(10);
	/*
	在alarm和read之间若cpu调度很慢导致alarm超时了还没有执行read时，
	到了执行read依然还有可能阻塞的，这在前面提到过了
	*/
	/*
	1.从标准输入读数据
	2.由于read在linux中是自动重启动的，
		因此当SIGALRM的handler返回时,read并不会被中断,
		也就是设置该定时器并不起作用
	3.这里只是说明有必要中断慢速系统调用，10.14节进行更详细的讨论
	*/
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
		err_sys("read error");
	}
	//取消定时器
	alarm(0);
	//写到标准输出
	write(STDOUT_FILENO, line, n);
	exit(0);
}

// SIGALRM的信号hanlder
static void sig_alrm(int signo) {
	/* nothing to do, just return to interrupt the read */
	printf("SIGALRM handler exec\n");
}
