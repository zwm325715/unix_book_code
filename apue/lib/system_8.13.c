#include <apue.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
/*
	图8-22中的程序是system函数的一种实现().
	它对信号没有进行处理(10.18节将修改使其进行信号处理:system_10.18.c)
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
		//执行shell:成功执行时，不返回；执行出错时，返回-1
		printf("------开始调用execl-----------\n");
		int res = execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		printf("execl执行成功或失败都不会跑下面的代码了\n");
		//退出码110(这里从127改成了110，避免与标准输出的exit status误解)
		//,该退出状态不会返回给调用方
		_exit(110);	/* execl error */
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
