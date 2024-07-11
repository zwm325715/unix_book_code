#include "apue.h"
#include <sys/wait.h>

//循环从标准输入读取命令，然后执行这些命令
int main(void) {
	char	buf[MAXLINE];	/* from apue.h */
	//子进程pid
	pid_t	pid;
	//子进程的终止状态:可以准确地判定子进程是如何终止的
	int		status;

    /* print prompt (printf requires %% to print %) 
	  打印提示(需要2个%%来打印出一个%)
	*/
	printf("%% ");	
    /*
      1.循环从"标准输入"一次读取一行,放到buf中
      2.当键入文件结束符(ctrl+D)作为行的第一个字符时,
        fgets返回一个null指针,于是while循环停止.
	  3.标准输入/输出均为行缓冲方式，每次调用fgets时会自动flush标准输出设备 
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
		//创建子进程
		if ((pid = fork()) < 0) {//创建失败时
			err_sys("fork error");
		} else if (pid == 0) {	/* child 只会在子进程中执行(父进程永远不会为0)*/
			//执行新程序文件:执行从标准输入读入的命令
			execlp(buf, buf, (char *)0);
			//跑到这里时就是出错了
			err_ret("couldn't execute: %s", buf);
			exit(127);//子进程退出(父进程不会退出哦)
		}

		/* parent 父进程会执行到这里*/
		//父进程等待子进程(pid)终止,终止状态放到status中
		if ((pid = waitpid(pid, &status, 0)) < 0) {
			err_sys("waitpid error");
		}	
		printf("%% ");
	}
	exit(0);
}
