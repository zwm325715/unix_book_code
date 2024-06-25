#include "apue.h"
#include <sys/wait.h>

//从标准输入读取命令，然后执行这些命令
int main(void) {
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

    /* print prompt (printf requires %% to print %) 打印提示*/
	printf("%% ");	
    /*
      1.从标准输入一次读取一行,放到buf中
      2.当键入文件结束符(ctrl+D)作为行的第一个字符时,
        fgets返回一个null指针,于是while循环停止.
    */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
        /**
            1.strlen的结果不包括尾零.
            2.fgets返回的每一行都以换行符(\n)终止,后随一个null字节:
               因此这里用strlen可以计算buf里面的数据长度，然后把换行符替换为null.
        */
		if (buf[strlen(buf) - 1] == '\n') {
            /* replace newline with null 替换为null(0)*/
            //原因:execlp函数要求的参数以"null"结束而不是以"换行符"结束.
			buf[strlen(buf) - 1] = 0; 
        }

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {	/* child */
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
