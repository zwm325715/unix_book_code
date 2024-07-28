#include "apue.h"
#include <errno.h>

//图10-14 为进程打印当前信号屏蔽字
void pr_mask(const char *str) {
	sigset_t	sigset;
	int			errno_save;
	/* we can be called by signal handlers */
	errno_save = errno;	//保存errno
	//不改变当前进程的信号屏蔽字(set为空指针)，但放到sigset中
	if (sigprocmask(0, NULL, &sigset) < 0) {
		err_ret("sigprocmask error");
	} else {
		printf("%s", str);//输出入参
		//仅测试下面几个信号是否在信号集中
		if (sigismember(&sigset, SIGINT))//SIGINT
			printf(" SIGINT in sigset!");
		if (sigismember(&sigset, SIGQUIT))//SIGQUIT
			printf(" SIGQUIT in sigset!");
		if (sigismember(&sigset, SIGUSR1))//SIGUSR1
			printf(" SIGUSR1 in sigset!");
		if (sigismember(&sigset, SIGALRM))//SIGALRM
			printf(" SIGALRM in sigset!");
		printf("\n");
	}
	/* restore errno 恢复errno*/
	errno = errno_save;
}
