#include "apue.h"
// 图4-23:chdir函数
int main(void) {
	//更改当前进程的工作目录到/tmp
	if (chdir("/tmp") < 0)
		err_sys("chdir failed");
	printf("chdir to /tmp succeeded\n");
	exit(0);
}
