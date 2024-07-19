#include	<sys/wait.h>
#include	<errno.h>
#include	<unistd.h>
/*
	图8-22中的程序是system函数的一种实现().
	它对信号没有进行处理(10.18节将修改使其进行信号处理)
*/
/* version without signal handling */
int system(const char *cmdstring) {
	pid_t	pid;
	int		status;

	if (cmdstring == NULL)
		return(1);/* always a command processor with UNIX */
	//创建子进程
	if ((pid = fork()) < 0) {//失败
		/* probably out of processes */
		status = -1;	
	} else if (pid == 0) {/* 子进程 child */
		//执行shell
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		//退出码127
		_exit(127);		/* execl error */
	} else { /* 父进程 parent */
		//循环执行给pid收尸直到成功，退出状态保存到status，
		while (waitpid(pid, &status, 0) < 0) {
			//非中断错误码时，停止循环
			if (errno != EINTR) {
				/* error other than EINTR from waitpid() */
				status = -1; 
				break;
			}
		}
	}

	return(status);
}
