#include "apue.h"

#define	BUFFSIZE	10
// 图3-5:只使用read和write函数复制一个文件
int main(void) {
	int		n;
	char	buf[BUFFSIZE];
	//读满了buf或者碰到换行符就返回
	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		printf("读取到了%d个字节\n",n);
		printf("开始写到标准输出...\n");	
		//碰到中文时正好处于2次write时就会乱码
		if (write(STDOUT_FILENO, buf, n) != n) {
			err_sys("write error");
		}
		printf("写到标准输出成功!\n");	
	}

	if (n < 0)
		err_sys("read error");

	exit(0);
}
