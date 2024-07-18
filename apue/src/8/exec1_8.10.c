#include "apue.h"
#include <stdio.h>
#include <sys/wait.h>
//字符串数组
char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

// 拼接字符串
#define PROJECT_DIR_FILE_STR(x,y) x#y
#define STR1(R) #R
#define STR2(R) STR1(R)
// 图8-16中的程序演示了exec函数
int main(void) {
	printf("rootdir=%s\n",STR2(ROOT_DIR));
	printf("PROJECT_DIR_FILE_STR=%s\n",PROJECT_DIR_FILE_STR(STR2(ROOT_DIR),echoall_8.10));
	pid_t	pid;
	//创建子进程
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	//子进程执行
		/*
		1.specify pathname, specify environment  
			指定pathname,指定环境变量
		2.通过"参数列表"和"新环境变量"的"路径名"方式执行新程序
			新程序:/home/sar/bin/echoall
			列表参数:"echoall", "myarg1","MY ARG2", (char *)0
			环境字符串数组:env_init
		*/
		if (execle(PROJECT_DIR_FILE_STR(STR2(ROOT_DIR),echoall_8.10),
				"echoall","myarg1","MY ARG2", (char *)0, 
				env_init) < 0)
			err_sys("execle error");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify filename, inherit environment */
		if (execlp("echoall","echoall", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}

	exit(0);
}
