#include "apue.h"
#include <fcntl.h>

//图4-8:access函数的使用方法
int main(int argc, char *argv[]) {
	if (argc != 2)
		err_quit("usage: a.out <pathname>");
	//用该main进程的"实际用户/组ID"测试能不能读"argv[1]"文件
	if (access(argv[1], R_OK) < 0)
		err_ret("access error for %s", argv[1]);
	else
		printf("read access OK\n");

	//只读打开该文件(用main进程的"有效用户/组ID"去跟"argv[1]"比)
	if (open(argv[1], O_RDONLY) < 0)
		err_ret("open error for %s", argv[1]);
	else
		printf("open for reading OK\n");
	exit(0);
}
