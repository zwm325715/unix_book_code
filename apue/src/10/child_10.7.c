#include	"apue.h"
#include <stdio.h>
#include	<sys/wait.h>

static void	sig_cld(int);
/*
  图10-6 不能正常工作的System V SIGCLD处理程序：
	程序在某些传统的System V平台上会一行行地不断重复输出"SIGCLD received"
	，最后进程用完其栈空间并异常终止
*/
int main() {
	pid_t	pid;
	//SIGCLD信号的handler为sig_cld函数
	if (signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	//创建子进程
	if ((pid = fork()) < 0) {
		perror("fork error");
	} else if (pid == 0) {/*子进程执行 child */
		printf("---child will sleep 2 seconds!\n");
		sleep(2);//休眠2秒
		printf("---child will sleep over and exit!\n");
		_exit(10);//退出
	}
	printf("parent will pause!\n");
	//父进程睡眠等待信号
	pause();/* parent */
	printf("parent wake up and exit!\n");
	exit(0);
}

/* interrupts pause() 中断睡眠 */
static void sig_cld(int signo) {
	pid_t	pid;
	int		status;

	printf("handler: SIGCLD received\n");
	/* 
	1.reestablish handler 
		重新设置handler
	2.对于System V的系统，通过上面的第2种语义：
		此时内核就会立即检查是否有子进程需要wait,
		由于我们正在处理SIGCLD信号，还没有进行wait，所以
		是存在的，于是乎它就产生另一个handler的调用，就
		产生死循环了。
	3.额外提一点:
		POSIX.1在信号发生时并没有将信号处理重置为默认值，
		于是在SIGCHLD的handler中不必再为该信号指定一个handler,
		也就是该行不需要了
	*/
	if (signal(SIGCLD, sig_cld) == SIG_ERR)	
		perror("signal error");
	/* fetch child status 取子进程状态*/
	if ((pid = wait(&status)) < 0)
		perror("wait error");
	printf("handler: pid = %d\n", pid);
	//输出子进程退出的状态码
	pr_exit(status);
}
