#include "apue.h"
#include <errno.h>

//两个出错函数的使用方法
int main(int argc, char *argv[]) {
    //1.指定errno为EACCES，还需要指定输出到标准错误stderr
	fprintf(stderr/*2*/, "EACCES: %s\n", strerror(EACCES));
    //2.伪造errno为ENOENT
	errno = ENOENT;
    //默认就是输出到标准错误，同时不需要传入errno了
	perror(argv[0]);//将shell执行时的命令:"当前程序名"作为了开头字符串
	exit(0);
}
