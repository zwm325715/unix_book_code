#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
//字符串数组
char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

// 图8-16中的程序演示了exec函数
int main(void) {
	pid_t	pid;
	printf("--------------1.execle------------------\n");
	//创建子进程
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	//子进程执行
		/*
		1.specify pathname, specify environment  
			指定pathname,指定环境变量
		2.通过"参数列表"和"新环境变量"的"路径名"方式执行新程序
			新程序:${workspace}/bin/echoall_8.10
			列表参数:"echoall", "myarg1","MY ARG2", (char *)0
			环境字符串数组:env_init (原来的PATH就没了)
		*/
		if (execle(PROJECT_DIR_FILE_STR(STR2(ROOT_DIR),echoall_8.10),
				"echoall","myarg1","MY ARG2", (char *)0, 
				env_init) < 0)
			err_sys("execle error");
	}
	//收尸
	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");
	printf("--------------2.execlp------------------\n");
	//把${workspace}/bin/8 目录追加到PATH环境变量中
	append_env_PATH(STR2(ROOT_DIR));
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	//子进程
		/* 
		1.specify filename, inherit environment 
		2.仅仅指定文件名，通过PATH环境变量去找该文件
		3.继承了父进程的PATH环境变量
		*/
		if (execlp("echoall_8.10",
			"echoall", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}
	//收尸
	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");
	exit(0);
}