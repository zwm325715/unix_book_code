#include "apue.h"

/* Reliable version of signal(), using POSIX sigaction().  
	signal()的可靠版本，使用POSIX的sigaction()实现
*/
//图10-18 用sigaction实现signal函数
Sigfunc * signal(int signo, Sigfunc *func) {
	struct sigaction act/*新handler*/, 
					 oact/*旧handler*/;
	//设置handler
	act.sa_handler = func;
	//清空信号集(不阻塞任何信号)
	sigemptyset(&act.sa_mask);
	//不需要选项(也就是不使用sa_sigaction)
	act.sa_flags = 0;
	//对于SIGALRM信号
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		/*
		由此信号中断的系统调用不自动重启动:
			理由是我们希望对I/O操作可以设置时间限制
		*/
		act.sa_flags |= SA_INTERRUPT;
#endif
	} else {//其他信号
		//中断的系统调用自动重启动
		act.sa_flags |= SA_RESTART;
	}
	//设置handler
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}
