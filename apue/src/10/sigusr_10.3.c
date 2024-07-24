#include "apue.h"

/* one handler for both signals */
static void	sig_usr(int);	
//图10-2 捕捉SIGUSR1和SIGUSR2的简单程序
int main(void) {
	//捕捉SIGUSR1信号，交给sig_usr函数处理
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR1");
	//捕捉SIGUSR2信号，交给sig_usr函数处理		
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR2");
	//死循环:挂起进程->等信号来->再挂起->等信号来->...
	for ( ; ; ) {
		//10.10节将说明pause函数,它使调用进程在接到一信号前"挂起"
		pause();//挂起进程
	}
}

/* 
	信号处理函数
	argument is signal number :参数是信号编号
*/
static void sig_usr(int signo) {
	//打印信号
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else //其它信号
		err_dump("received signal %d\n", signo);
}
