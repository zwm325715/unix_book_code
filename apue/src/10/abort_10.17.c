#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* POSIX-style abort() function */
//图10-25 abort的POSIX.1实现
void abort(void) {
	sigset_t			mask;
	struct sigaction	action;

	/* Caller can't ignore SIGABRT, if so reset to default */
	//SIGABRT重置为系统默认动作
	sigaction(SIGABRT, NULL, &action);
	//旧动作是忽略时
	if (action.sa_handler == SIG_IGN) {
		//置为默认
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}
	if (action.sa_handler == SIG_DFL) {
		/* flush all open stdio streams */
		fflush(NULL);//刷新所有标准I/O的缓冲区
	}

	/* 
	Caller can't block SIGABRT; make sure it's unblocked
	调用者不能阻塞SIGABRT;确保它不被阻塞
	*/
	sigfillset(&mask);//mask信号集包括所有信号
	/* 
	mask has only SIGABRT turned off 
	mask信号集中删除SIGABRT:也就是只有SIGABRT位关闭(置0)->不阻塞
	*/
	sigdelset(&mask, SIGABRT);
	//赋值信号屏蔽字(只有SIGABRT不阻塞)
	sigprocmask(SIG_SETMASK, &mask, NULL);
	/* send the signal 给自己发送SIGABRT信号*/
	//10.9节的最后说明：kill返回之前，SIGABRT信号就送给了进程
	kill(getpid(), SIGABRT);

	/* 
	If we're here, process caught SIGABRT and returned 
	程序走到这里时，说明进程已经捕获到了SIGABRT并且handler处理结束了
	*/
	fflush(NULL);/* flush all open stdio streams */
	action.sa_handler = SIG_DFL;
	/* reset to default 重置成默认*/
	sigaction(SIGABRT, &action, NULL);	
	/* just in case ... 以防万一*/
	sigprocmask(SIG_SETMASK, &mask, NULL);	
	kill(getpid(), SIGABRT);/* and one more time */
	exit(1);	/* this should never be executed ... */
}
