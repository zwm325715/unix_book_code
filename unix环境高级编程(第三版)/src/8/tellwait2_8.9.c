#include "apue.h"

static void charatatime(char *);
//修改上面实例8-12中的程序，使其使用TELL和WAIT函数以避免竞争条件，形成图8-13中的程序
int main(void) {
	pid_t	pid;
	//这里用信号实现的，后续学到再回来看
	TELL_WAIT();

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		/* parent goes first 父进程先运行*/
		WAIT_PARENT();//等待父进程
		charatatime("output from child\n");
	} else {
		charatatime("output from parent\n");
		//通知子进程
		TELL_CHILD(pid);
	}
	exit(0);
}

static void charatatime(char *str) {
	char	*ptr;
	int		c;

	setbuf(stdout, NULL);			/* set unbuffered */
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}
