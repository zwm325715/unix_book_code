#include "apue.h"
#include <sys/wait.h>
//图8-5:使用图8-4中的宏打印进程终止状态的说明
void pr_exit(int status) {
	//1.正常终止子进程返回的状态
	if (WIFEXITED(status)) {
		//取exit等函数的参数的低8位(1个字节,最大255)
		printf("normal termination, exit status = %d\n",
				WEXITSTATUS(status));
	//2.异常终止子进程返回的状态(没有捕捉的信号)
	}else if (WIFSIGNALED(status)) {
		//获取使子进程终止的信号编号
		printf("abnormal termination, signal number = %d%s\n",
				WTERMSIG(status),
// 当前os支持WCOREDUMP时(linux支持的)
// 但是如果定义了_POSIX_C_SOURCE功能测试宏(2.7节)，则有些平台会隐藏这个宏
#ifdef WCOREDUMP
				//是否已经产生终止子进程的core文件
				WCOREDUMP(status) ? " (core file generated)" : "");
#else
				"");
#endif
	//3.当前"暂停子进程"的返回的状态
	}else if (WIFSTOPPED(status)) {
		//获取使"子进程暂停"的信号编号
		printf("child stopped, signal number = %d\n",
				WSTOPSIG(status));
	}
}
