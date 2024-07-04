#include "apue.h"
#include <fcntl.h>
//图3-11:第1个参数指定fd，然后打印该fd的文件标志
int main(int argc, char *argv[]) {
	int		val;

	if (argc != 2)
		err_quit("usage: a.out <descriptor#>");
	//文件状态标志
	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
		err_sys("fcntl error for fd %d", atoi(argv[1]));
	
	//O_ACCMODE值为0003,0开头表示八进制,对应的2进制为0b0011，也就是只取最后2位即可
	switch (val & O_ACCMODE) {
		case O_RDONLY://只读
			printf("read only");
			break;

		case O_WRONLY://只写
			printf("write only");
			break;

		case O_RDWR://读写
			printf("read write");
			break;

		default:
			err_dump("unknown access mode");
	}
	//追加写
	if (val & O_APPEND)
		printf(", append");
	//非阻塞
	if (val & O_NONBLOCK)
		printf(", nonblocking");
	//等待物理I/O完成
	if (val & O_SYNC)
		printf(", synchronous writes");
//linux忽略:_POSIX_C_SOURCE为功能测试宏(2.7)
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC)
		printf(", synchronous writes");
#endif

	putchar('\n');
	exit(0);
}
