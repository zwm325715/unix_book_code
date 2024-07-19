#include "apue.h"
//图8-24 用system执行命令行参数
int main(int argc, char *argv[]) {
	int		status;

	if (argc < 2)
		err_quit("command-line argument required");
	/*
	1.进行system调用(执行fork+exec)：
		当被程序被赋予root权限(u+s)时在system中
		执行了fork和exec之后权限仍被保存下来，这是一个安全漏洞
	*/
	if ((status = system(argv[1])) < 0)
		err_sys("system() error");
	pr_exit(status);
	exit(0);
}
