#include "apue.h"
// 图5-12:tmpfile和tmpnam的应用
int main(void) {
	char	name[L_tmpnam], line[MAXLINE];
	FILE	*fp;
	/**
	编译时会有警告:
	tempfiles_5.13.c:(.text+0x11): warning: the use of `tmpnam' is dangerous, better use `mkstemp'
	*/
	/* first temp name 第一个路径名:参数为NULL，也就是被放到了静态区*/
	printf("%s\n", tmpnam(NULL));		
	/* second temp name 第2个路径名:参数不为NULL,放到了name字符数组中*/
	tmpnam(name);	
	printf("%s\n", name);//打印到标准输出

	/* create temp file 创建临时文件，返回文件指针*/
	if ((fp = tmpfile()) == NULL) 
		err_sys("tmpfile error");
	/* write to temp file 写到该临时文件中*/
	fputs("one line of output\n", fp);	
	/* then read it back 将fp文件的偏移量设置到文件的起始位置.
	1.这里用到了那条规则:
		如果没有fflush、fseek、fsetpos或rewind操作,
		则在输出(fputs)的后面不能直接跟随输入(fgets).
	*/
	rewind(fp);		
	//把fp文件指针背后的流的数据读到字符数组line中
	if (fgets(line, sizeof(line), fp) == NULL)
		err_sys("fgets error");
	/* print the line we wrote 把line字符串输出到标准输出*/
	fputs(line, stdout);

	exit(0);
}
