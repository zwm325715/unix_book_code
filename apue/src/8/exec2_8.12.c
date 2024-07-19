#include "apue.h"
#include <sys/wait.h>
//图8-20:执行一个解释器文件的程序
int main(void) {
	pid_t	pid;
	//创建子进程
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {/* child 子进程执行*/
		/*
			1.解释器文件(bin/testinterp)，通过cmake的file命令生成
			2.testinterp使用的解释器就是图7-4的程序
		*/
		if (execl(PROJECT_DIR_FILE_STR(STR2(ROOT_DIR),testinterp),
				"unpass_arg","testinterp", "myarg1", "MY ARG2", (char *)0) < 0) {
			err_sys("execl error");
		}
	}
	//等待子进程
	if (waitpid(pid, NULL, 0) < 0)	/* parent */
		err_sys("waitpid error");
	exit(0);
}
