#include "apue.h"

#define	BUFFSIZE	4096  //4k缓冲区大小

//可用于复制任一UNIX普通文件
int main(void) {
	int		n;//读取到的字节数
	char	buf[BUFFSIZE];//缓冲区
    /*
      从标准输入读取所有数据放到buf中
        -到达文件尾时read返回0
        -发生错误时,返回-1
    */
	while ((n = read(STDIN_FILENO/*0*/, buf, BUFFSIZE)) > 0) {
        //buf数据写n个字节到标准输出
		if (write(STDOUT_FILENO/*1*/, buf, n) != n) {
			err_sys("write error");
        }
    }

	if (n < 0) {
		err_sys("read error");
    }

	exit(0);
}
