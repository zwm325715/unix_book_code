#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char	buf[500000];
//图14-1 长的非阻塞write
int main(void) {
	int		ntowrite, nwrite;
	char	*ptr;
	//从标准输入读，最多读入500000个
	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	//输出
	fprintf(stderr, "read %d bytes\n", ntowrite);
	/* 
		set nonblocking 
		标准输出fd设置为非阻塞I/O
	*/
	set_fl(STDOUT_FILENO, O_NONBLOCK);

	ptr = buf;
	while (ntowrite > 0) {
		errno = 0;
		//写到标准输出
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		//错误信息输出到标准错误
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		//处理写入错误的情况(比如EAGAIN时就会返回-1)
		if (nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	/* clear nonblocking 关闭非阻塞I/O位*/
	clr_fl(STDOUT_FILENO, O_NONBLOCK);	

	exit(0);
}
