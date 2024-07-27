#include "apue.h"
#include <errno.h>

//图10-14 为进程打印信号屏蔽字
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
		//仅测试下面几个信号位是否开启(阻塞)
		if (sigismember(&sigset, SIGINT))//SIGINT
			printf(" SIGINT");
		if (sigismember(&sigset, SIGQUIT))//SIGQUIT
			printf(" SIGQUIT");
		if (sigismember(&sigset, SIGUSR1))//SIGUSR1
			printf(" SIGUSR1");
		if (sigismember(&sigset, SIGALRM))//SIGALRM
			printf(" SIGALRM");
		printf("\n");
	}
	/* restore errno 恢复errno*/
	errno = errno_save;
}
