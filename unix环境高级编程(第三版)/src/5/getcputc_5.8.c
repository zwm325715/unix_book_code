#include "apue.h"
//图5-4:类似于图3-4程序，使用getc和putc将标准输入复制到标准输出
//也可以用fgetc和fputc来实现
int main(void) {
	int		c;
	//从标准输入的文件指针stdin中读取一个字符，没有到达尾端或出错(EOF)时
	while ((c = getc(stdin)) != EOF)
		//输出到标准输出(文件指针为stdout)
		if (putc(c, stdout) == EOF)
			err_sys("output error");
	//getc出错时:标准输入
	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
