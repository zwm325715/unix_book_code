#include "apue.h"
//图5-5:用fgets和fputs将标准输入复制到标准输出
int main(void) {
	char	buf[MAXLINE];//4096
	//读取一行，读到buf中;到达尾端或出错时，返回NULL
	while (fgets(buf, MAXLINE, stdin) != NULL)
		//把缓冲区中的字符串写到标准输出；出错时，返回EOF
		if (fputs(buf, stdout) == EOF)
			err_sys("output error");
	//判断fgets是否是因为出错而走到这里
	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
