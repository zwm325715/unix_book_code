#include "apue.h"
#include <stdio.h>
/* 
set nonzero by signal handler
通过信号handler设置为非0
1.写该变量是不能被中断的(sig_atomic_t)
2.同时是易变的(volatile):main和异步执行的handler都会访问
 */
volatile sig_atomic_t	quitflag;//全局变量
/* 
one signal handler for SIGINT and SIGQUIT 
信号SIGINT和SIGQUIT的handler
*/
static void sig_int(int signo) {
	if (signo == SIGINT)//SIGINT信号时
		printf("\ninterrupt\n");
	else if (signo == SIGQUIT) //SIGQUIT信号时
		/* set flag for main loop */
		quitflag = 1;//全局变量设置为1
}

//图10-23 用sigsuspend等待一个全局变量被设置
int main(void) {
	sigset_t newmask, oldmask, zeromask;
	//注册handler
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	if (signal(SIGQUIT, sig_int) == SIG_ERR)
		err_sys("signal(SIGQUIT) error");
	//清空信号集
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	//SIGQUIT添加到newmask中
	sigaddset(&newmask, SIGQUIT);

	/*
	 Block SIGQUIT and save current signal mask.
	 阻塞SIGQUIT并保存旧值
	 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
	/*
	1.当全局变量quitflag还没有被设置(0)时，就挂起
	2.碰到SIGQUIT时,去执行handler->quitflag变为1,while不再执行挂起
	*/
	while (quitflag == 0) {
		//不添加新的阻塞信号，但是要挂起进程
		sigsuspend(&zeromask);
	}

	printf("\nquitflag is set,main process continue!\n");
	/*
	 SIGQUIT has been caught and is now blocked; do whatever.
	 SIGQUIT被捕获，现在被阻塞;想做什么就做什么.
	 */
	quitflag = 0;

	/*
	 Reset signal mask which unblocks SIGQUIT.
	 恢复信号屏蔽字，解除SIGQUIT阻塞
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	exit(0);
}
