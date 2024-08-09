#include "apue.h"
#include <unistd.h>

//图10-24 父子进程用信号来实现同步

/* set nonzero by sig handler */
static volatile sig_atomic_t sigflag; 
static sigset_t newmask, oldmask, zeromask;

/* one signal handler for SIGUSR1 and SIGUSR2 */
//SIGUSR1和SIGUSR2的信号handler
static void sig_usr(int signo) {
	sigflag = 1;
}
//阻塞SIGUSR1和SIGUSR2 信号
void TELL_WAIT(void) {
	//设置handler
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR2) error");
	//清空信号集	
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	/* Block SIGUSR1 and SIGUSR2, and save current signal mask */
	//阻塞SIGUSR1和SIGUSR2信号并保存旧值
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
}
//等待父进程
void WAIT_PARENT(void) {
	//全局变量sigflag没有被设置值时
	while (sigflag == 0) {
		/* and wait for parent */
		//进程挂起等待(信号屏蔽字更改为不阻塞任何信号)
		//捕捉到任何一个信号(包括SIGUSR1,SIGUSR2)时sigsuspend会返回
		printf("进程挂起,pid=%d\n",getpid());
		sigsuspend(&zeromask);
		printf("进程被唤醒,pid=%d\n",getpid());
	}
	//重置为0
	sigflag = 0;

	/* Reset signal mask to original value */
	//恢复旧的信号屏蔽字
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
}
//等子进程
void WAIT_CHILD(void) {
	while (sigflag == 0) {
		/* and wait for child */
		//进程挂起等信号
		sigsuspend(&zeromask);	
	}
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
}

//告诉子进程
void TELL_CHILD(pid_t pid) {
	/* tell child we're done */
	kill(pid, SIGUSR1);//发送SIGUSR1信号
}
//告诉父进程
void TELL_PARENT(pid_t pid) {
	/* tell parent we're done */
	//将SIGUSR2信号发给父进程
	kill(pid, SIGUSR2);		
}
