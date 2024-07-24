#include "apue.h"
#include <errno.h>
#include <stdio.h>
/**
	1.子进程为挂断信号(SIGHUP:系统默认动作是终止该进程)设立handler,
	  可以观察SIGHUP信号是否已经发送给子进程
	2.POSIX.1要求向"新孤儿进程组"中处于"停止状态"的每一个进程发送挂断信号(SIGHUP),
	  接着又向其发送继续信号(SIGCONT).
	  -此程序在父进程终止后，进程组包含一个停止的进程，进程组成为了孤儿进程组.
*/
static void sig_hup(int signo) {
	printf("SIGHUP received, pid = %ld\n", (long)getpid());
}
//打印一系列进程ID信息
static void pr_ids(char *name) {
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
	    name, 
		(long)getpid(), //进程ID
		(long)getppid(), //父进程ID
		(long)getpgrp(),//调用进程的进程组ID
	    (long)tcgetpgrp(STDIN_FILENO)/*返回前台进程组ID*/);
	//清空缓冲区	
	fflush(stdout);
}

// 实例9-12创建一个孤儿(orphan /ˈɔːf(ə)n/)进程组
int main(void) {
	char	c;
	pid_t	pid;
	//父进程信息
	pr_ids("parent");
	//创建进程
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) { /* parent 父进程执行*/
		/* 
			sleep to let child stop itself 
			1.让子进程终止(权宜之计)
			2.父进程终止时，子进程称为孤儿进程(父进程变为init)
			  此时子进程称为孤儿进程组的成员
		*/
		sleep(5);		
	} else {/* child 子进程执行*/
		pr_ids("child");//子进程信息
		/* establish signal handler 设立信号handler*/
		signal(SIGHUP, sig_hup);
		printf("child will stop by signal SIGTSTP!but not terminate~\n");
		/* 
		stop ourself 终止自己
		1.子进程使用kill向其自身发送停止(SIGTSTP)信号
			这将停止子进程，类似于用终端挂起字符(ctrl+Z)停止一个前台作业
		2.子进程停止了，此时变成了一个新的"孤儿进程组"了，
			内核会发送SIGHUP->SIGCONT信号给该子进程
		3.子进程恢复执行的代码顺序
			sig_hup()打印-> 继续执行kill下面的代码
		*/
		kill(getpid(), SIGTSTP);	
		printf("child wake up\n");
		/* prints only if we're continued 打印*/
		pr_ids("child");//注意此时父进程变成init了，其他没变
		//读标准输入
		// if (read(STDIN_FILENO, &c, 1) != 1) {
		// 	printf("read error %d on controlling TTY\n", errno);
		// }
	}
	exit(0);
}
