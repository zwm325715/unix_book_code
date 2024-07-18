#include "apue.h"

void	pr_stdio(const char *, FILE *);
int		is_unbuffered(FILE *);
int		is_linebuffered(FILE *);
int		buffer_size(FILE *);

//图5-11程序为3个标准流以及1个普通文件相关联的流打印有关"缓冲的状态"信息
int main(void) {
	FILE	*fp;
	//输出到标准输出
	fputs("enter any character\n", stdout);
	//从标注输入读取一个字符(到达尾端或出错时返回EOF)
	if (getchar() == EOF)//对于linux：ctrl+d就是键入"文件终止符"
		err_sys("getchar error");
	//输出到标准错误
	fputs("one line to standard error\n", stderr);
	//1.依次输出3个标准流的"缓冲区类型"和"大小"
	pr_stdio("stdin",  stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);
	//2.打开/etc/passwd文件
	if ((fp = fopen("/etc/passwd", "r")) == NULL)
		err_sys("fopen error");
	//读一个字符(只是没有使用这个字符)
	if (getc(fp) == EOF)
		err_sys("getc error");
	//再次打印这个普通文件流的"缓冲区类型"和"大小"
	pr_stdio("/etc/passwd", fp);
	exit(0);
}
//接收文件指针，判断fp的缓冲类型
void pr_stdio(const char *name, FILE *fp) {
	//当前是"哪个流"输出到标准输出
	printf("stream = %s, ", name);
	//判断有没有缓冲(通过flags成员判断)
	if (is_unbuffered(fp))
		printf("unbuffered");
	// 判断是否"行缓冲"	
	else if (is_linebuffered(fp))
		printf("line buffered");
	else /* if neither of above 其他情况就是全缓冲*/ 
		printf("fully buffered");
	//输出缓冲区的大小	
	printf(", buffer size = %d\n", buffer_size(fp));
}
//不可移植
#if defined(_IO_UNBUFFERED)  //_IO_UNBUFFERED 忽略

int is_unbuffered(FILE *fp) {
	return(fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE *fp) {
	return(fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp) {
	return(fp->_IO_buf_end - fp->_IO_buf_base);
}

#elif defined(__SNBF)  //_SNBF 忽略

int is_unbuffered(FILE *fp) {
	return(fp->_flags & __SNBF);
}

int is_linebuffered(FILE *fp) {
	return(fp->_flags & __SLBF);
}

int buffer_size(FILE *fp) {
	return(fp->_bf._size);
}

#elif defined(_IONBF) //_IONBF 走这里

#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif
//判断是否"无缓冲"
int is_unbuffered(FILE *fp) {
	return(fp->_flags & _IONBF);
}

//判断是否"行缓冲"
int is_linebuffered(FILE *fp) {
	return(fp->_flags & _IOLBF);
}

//缓冲区大小
int buffer_size(FILE *fp) {
#ifdef _LP64
	// return(fp->_base - fp->_ptr);
	//用"预留区域的尾端"-"预留区域的起始"
	return(fp->_IO_buf_end - fp->_IO_buf_base);
#else
	return(BUFSIZ);	/* just a guess */
#endif
}

#else

#error unknown stdio implementation!

#endif
