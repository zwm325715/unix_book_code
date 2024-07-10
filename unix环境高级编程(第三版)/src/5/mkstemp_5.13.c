#include "apue.h"
#include <errno.h>

void make_temp(char *template);
// 图5-13:显示了如何使用mkstemp函数
int main() {
	/* right way 正确的方式
	1.使用了字符数组来声明的字符串模版:
	  名字是分配在栈上的，mstemp时可以修改其内容
	*/
	char	good_template[] = "/tmp/dirXXXXXX";	
	/* wrong way 错误的方式:会发生段错误
	1.使用的指针来声明的字符串模版:
		此时只有指针自身驻留在栈上,
		编译器把"字符串"存放在可执行文件的"只读段",
		当mstemp函数试图修改字符串时,出现了段错误.
	*/
	char	*bad_template = "/tmp/dirXXXXXX";	

	printf("trying to create first temp file...\n");
	make_temp(good_template);//正常处理
	printf("trying to create second temp file...\n");
	make_temp(bad_template);//会有段错误发生
	exit(0);
}

void make_temp(char *template) {
	int			fd;
	struct stat	sbuf;
	/*
	 1.创建临时普通文件，并返回对应的fd
	 2.bag_template用指针类型创建的字符串传进来时，
	 	调用mkstemp时会发生段错误
	*/
	if ((fd = mkstemp(template)) < 0)
		err_sys("can't create temp file");
	//输出到标准输出
	printf("temp name = %s\n", template);
	//需要我们手工关闭掉它(mkstemp不会自动关闭)
	close(fd);
	//查看该文件的信息
	if (stat(template, &sbuf) < 0) {
		//没有该文件
		if (errno == ENOENT)
			printf("file doesn't exist\n");
		else
			err_sys("stat failed");
	} else {
		//文件还存在
		printf("file exists\n");
		//解除链接后才会被删除
		unlink(template);
	}
}
