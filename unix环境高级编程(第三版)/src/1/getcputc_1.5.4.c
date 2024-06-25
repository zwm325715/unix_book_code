#include "apue.h"
#include <stdio.h>

//类似mycat_1.5.3的程序.
//将标准输入复制到标准输出
int main(void) {
	int		c;
	//getc来自标准库(man 3):一次读取一个字符，这里是从标准输入(stdin)，直到文件尾
	while ((c = getc(stdin)) != EOF)
		//将字符c写入到标准输出(stdout)
		if (putc(c, stdout) == EOF)
			err_sys("output error");

	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
