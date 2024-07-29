#include "apue.h"

#define	BUFFSIZE	1024
/* signal handler for SIGTSTP */
static void sig_tstp(int signo)	{
	sigset_t	mask;

	/* ... move cursor to lower left corner, reset tty mode ... */

	/*
	 * Unblock SIGTSTP, since it's blocked while we're handling it.
	 */
	sigemptyset(&mask);
	sigaddset(&mask, SIGTSTP);
	//解除SIGTSTP阻塞(捕捉该信号期间系统自动阻塞这个信号)
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	/* reset disposition to default 将配置重置为默认值*/
	signal(SIGTSTP, SIG_DFL);
	/* and send the signal to ourself 给自己发SIGTSTP信号*/
	kill(getpid(), SIGTSTP);	
	//此时进程stoped，当fg命令发来的SIGCONT信号，该进程会继续
	/* we won't return from the kill until we're continued */
	/* reestablish signal handler 重新设置handler来做处理(绘制屏幕) */
	signal(SIGTSTP, sig_tstp);

	/* ... reset tty mode, redraw screen ... */
}
//图10-31 如何处理SIGTSTP
int main(void) {
	int		n;
	char	buf[BUFFSIZE];

	/*
	Only catch SIGTSTP if we're running with a job-control shell.
	只有我们在使用作业控制shell运行时才捕获SIGTSTP信号
	 */
	//忽略SIG_IGN信号，只有作业控制shell才会将这3个信号重新设置为SIG_DFL 
	if (signal(SIGTSTP, SIG_IGN) == SIG_DFL){
		//设置为sig_tstp
		signal(SIGTSTP, sig_tstp);
	}
	
	//从标准输入读
	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		//写到标准输出
		if (write(STDOUT_FILENO, buf, n) != n) {
			err_sys("write error");
		}	
	}

	if (n < 0)
		err_sys("read error");

	exit(0);
}
