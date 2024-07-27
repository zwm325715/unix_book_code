#include "apue.h"

static void	sig_quit(int);
//图10-15 信号设置和sigprocmask实例
int main(void) {
	sigset_t	newmask,//阻塞信号集 
				oldmask, //旧的阻塞信号集
				pendmask/*阻塞信号集*/;
	//设置SIGQUIT信号处理函数为sig_quit
	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("can't catch SIGQUIT");

	/*
	 * Block SIGQUIT and save current signal mask.
	 */
	//清除信号集 
	sigemptyset(&newmask);
	//信号集增加SIGQUIT
	sigaddset(&newmask, SIGQUIT);
	//把信号集newmask追加到当前进程的信号屏蔽字中，旧的屏蔽字放到oldmask中
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
	printf("main: sleeping 5s!\n");	
	/* SIGQUIT here will remain pending SIGQUIT信号未决(阻塞)*/
	sleep(5);//睡5s
	printf("\nmain: wakeup!\n");
	//取当前进程的阻塞信号集放到pendmask中
	if (sigpending(&pendmask) < 0)
		err_sys("sigpending error");
	//测试SIGQUIT信号是否阻塞
	if (sigismember(&pendmask, SIGQUIT))
		printf("main:SIGQUIT pending\n");

	/*恢复信号掩码，解除SIGQUIT阻塞。
	 * Restore signal mask which unblocks SIGQUIT.
	 */
	printf("main:SIGQUIT will unblock\n");
	printf("main:sigprocmask函数返回之前，内核就会投递SIGQUIT信号\n");
	/*
		1.恢复信号屏蔽字 
		2.注意:
		如果我们提供一个函数供别人使用时，必须使用SIG_SETMASK恢复，
		而不能用SIG_UNBLOCK，因为调用者也之前就可能阻塞了该信号.
	*/
	if (sigprocmask(SIG_SETMASK/*赋值*/, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
	printf("SIGQUIT unblocked\n");
	/* 
		SIGQUIT here will terminate with core file 
		此时SIGQUIT会终止进程并产生core文件
	*/
	sleep(5);	
	exit(0);
}
//SIGQUIT的handler
static void sig_quit(int signo) {
	printf("---SIGQUIT handler:caught SIGQUIT\n");
	//SIGQUIT设置为系统默认动作(终止+core)
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		err_sys("can't reset SIGQUIT");
}
