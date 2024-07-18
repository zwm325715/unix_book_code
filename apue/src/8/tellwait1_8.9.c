#include "apue.h"

static void charatatime(char *);
/**
	实例8-12输出2个字符串分别由父子进程输出
 		依赖于内核调度父子进程运行的顺序和时间片，所以该程序包含了一个竞争条件
*/
int main(void) {
	pid_t	pid;
	//创建新进程
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {//子进程
		charatatime("output from child\n");
	} else {//父进程
		charatatime("output from parent\n");
	}
	exit(0);
}

static void charatatime(char *str) {
	char	*ptr;
	int		c;
	/*
	  关闭标准I/O中对"标准输出"的缓冲:
        每个字符都需要调用一次write系统调用，目的是使
		内核能尽可能多次地在两个进程之间进行切换
	*/
	setbuf(stdout, NULL); /* set unbuffered */
	//遍历每个字符
	for (ptr = str; (c = *ptr++) != 0; ) {
		//把该字符输出到"标准输出":有几率父子进程乱序输出
		putc(c, stdout);
	}
}
