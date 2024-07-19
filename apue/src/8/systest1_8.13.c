#include "apue.h"
#include <sys/wait.h>

//图8-23 调用system函数
int main(void) {
	int		status;
	//1.正常命令字符串
	if ((status = system("date")) < 0)
		err_sys("system() error");
	//输出结果状态
	pr_exit(status);
	//2.异常命令字符串
	if ((status = system("nosuchcommand")) < 0)
		err_sys("system() error");
	pr_exit(status);
	//3.正常命令字符串，且指定了退出状态
	if ((status = system("who; exit 44")) < 0)
		err_sys("system() error");
	pr_exit(status);

	exit(0);
}
