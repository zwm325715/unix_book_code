#include "apue.h"
#include <sys/wait.h>
//信号之中断函数
static void	sig_int(int);		/* our signal-catching function */

//从标准输入读命令并执行(带信号处理)
int main(void) {
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;
    //通过signal来指定SIGINT信号处理函数为sig_int
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {		/* child */
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}

void sig_int(int signo) {
	printf("interrupt\n%% ");
}
