#include	<sys/wait.h>
#include	<errno.h>
#include	<signal.h>
#include	<unistd.h>

//图10-28 system函数的POSIX.1正确实现
/* 
with appropriate(/əˈprəʊpriət/ 合适的;恰当的) signal handling 
适当的信号处理
*/
int system(const char *cmdstring){
	pid_t				pid;
	int					status;
	struct sigaction	ignore, saveintr, savequit;
	sigset_t			chldmask, savemask;

	if (cmdstring == NULL)
		return(1);/* always a command processor with UNIX */
	/* 
	ignore SIGINT and SIGQUIT 
	1.忽略SIGINT和SIGQUIT 
	*/
	ignore.sa_handler = SIG_IGN;//忽略
	//清空屏蔽信号集
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	//设置信号SIGINT和SIGQUIT的handler(忽略)
	if (sigaction(SIGINT, &ignore, &saveintr) < 0)
		return(-1);
	if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
		return(-1);

	//2.清空chldmask信号集
	sigemptyset(&chldmask);	/* now block SIGCHLD */
	//添加上SIGCHLD信号
	sigaddset(&chldmask, SIGCHLD);
	//阻塞SIGCHLD信号
	if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
		return(-1);

	//3.创建子进程
	if ((pid = fork()) < 0) {
		status = -1;	/* probably out of processes */
	} else if (pid == 0) {/*子进程执行 child */
		/* 
		restore previous signal actions & reset signal mask 
		恢复之前的"信号动作" 以及 "重置信号屏蔽字":
		1.	SIGINT和SIGQUIT不再忽略
		2.	子进程不再阻塞SIGCHLD信号
		*/
		sigaction(SIGINT, &saveintr, NULL);
		sigaction(SIGQUIT, &savequit, NULL);
		sigprocmask(SIG_SETMASK, &savemask, NULL);
		//3.exec执行
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);	/* exec error */
	} else {/* 父进程 parent */
		//4.等待子进程终止
		while (waitpid(pid, &status, 0) < 0) {
			if (errno != EINTR) {
				/* error other than EINTR from waitpid() */
				status = -1; 
				break;
			}
		}	
	}

	/* 
	restore previous signal actions & reset signal mask 
	恢复之前的"信号动作" 以及 "重置信号屏蔽字"
	*/
	if (sigaction(SIGINT, &saveintr, NULL) < 0)
		return(-1);
	if (sigaction(SIGQUIT, &savequit, NULL) < 0)
		return(-1);
	if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
		return(-1);

	return(status);
}
