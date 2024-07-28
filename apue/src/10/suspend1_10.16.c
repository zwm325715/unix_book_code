#include "apue.h"

static void	sig_int(int);
//图10-22 保护临界区不被信号中断
int main(void) {
	sigset_t	newmask, oldmask, waitmask;

	pr_mask("program start --- blocked signal: ");
	//设置SIGINT信号handler为sig_int
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	//waitmask信号集清空
	sigemptyset(&waitmask);
	//SIGUSR1和SIGUSR2添加到waitmask信号集中
	sigaddset(&waitmask, SIGUSR1);
	sigaddset(&waitmask, SIGUSR2);

	//newmask信号集清空
	sigemptyset(&newmask);
	//SIGINT添加到newmask信号集中
	sigaddset(&newmask, SIGINT);

	/*
	 Block SIGINT and save current signal mask.
	 阻塞SIGINT并且保存当前的信号屏蔽字
	 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");

	/*
	 Critical region of code.
	 临界区代码
	 */
	pr_mask("in critical region --- blocked signal: ");

	/*
	 Pause, allowing all signals except SIGUSR1和SIGUSR2.
	 暂停,允许所有的信号除了SIGUSR1和SIGUSR2
	 1.进程挂起，并将waitmask信号集中的信号都添加到进程的信号屏蔽字中
	 2.sigsuspend返回时，它将信号屏蔽字设置为调用它之前的
	 */
	if (sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error");
	
	pr_mask("after return from sigsuspend --- blocked signal: ");

	/*
	 Reset signal mask which unblocks SIGINT.
	 恢复信号屏蔽字，解除SIGINT阻塞
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	/*
	 And continue processing ...
	 继续处理
	 */
	pr_mask("program exit--- blocked signal: ");

	exit(0);
}
//SIGINT信号handler
static void sig_int(int signo) {
	pr_mask("\n---in sig_int handler--- blocked signal: ");
}
