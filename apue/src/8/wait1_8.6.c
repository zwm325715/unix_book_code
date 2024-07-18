#include "apue.h"
#include <sys/wait.h>
// 图8-6中程序调用pr_exit函数，演示终止状态的各种值
int main(void) {
	pid_t	pid;
	int		status;
	//1.创建一个子进程，存下来子进程id
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	}else if (pid == 0){/* child 子进程*/ 
		//直接正常退出，状态为7
		exit(7);
	}
	//父进程等待子进程终止(必须是创建的这个子进程),终止状态放到status中
	if (wait(&status) != pid){/* wait for child */
		err_sys("wait error");
	}
	//打印正常终止状态信息
	pr_exit(status);/* and print its status */

	//2.创建一个子进程，存下来子进程id
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	}else if (pid == 0){/*子进程执行 child */
		//产生SIGABRT异常终止信号
		abort(); /* generates SIGABRT */
	}
	//父进程等待子进程终止(必须是创建的这个子进程),终止状态放到status中
	if (wait(&status) != pid) {/* wait for child */
		err_sys("wait error");
	}
	//打印异常终止状态信息
	pr_exit(status); /* and print its status */

	//3.创建一个子进程，存下来子进程id
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	}else if (pid == 0)	{/*子进程执行 child */
		//除数为0:内核产生SIGFPE信号
		status /= 0;/* divide by 0 generates SIGFPE */
	}
	//父进程等待子进程终止,终止状态放到status中
	if (wait(&status) != pid) {/* wait for child */
		err_sys("wait error");
	}
	//打印异常终止状态信息
	pr_exit(status);/* and print its status */

	exit(0);
}
