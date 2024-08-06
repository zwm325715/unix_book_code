#include "apue.h"
#include <fcntl.h>

/* 
	图3-12:对一个fd设置一个或多个文件状态标志的函数
	flags are file status flags to turn on
 */
void set_fl(int fd, int flags) {
	int		val;
	//1.先获取文件状态标志
	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");
	/*
	2.按照期望修改(执行或位运算):
		参考F_SETFL可以设置哪些文件状态标志,这些都是可以通过或位运算添加进去
		比较经典比如O_NONBLOCK
	*/
	val |= flags;		/* turn on flags 打开*/
	// val &= ~flags;		/* turn off flags 关闭*/
	
	//3.最后设置新标志值
	if (fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
}

/* 
	flags are the file status flags to turn off
	关掉文件状态标志
 */
void clr_fl(int fd, int flags) {
	int		val;
	//取到原来的
	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");
	//取反做与运算  就是关闭该位了
	val &= ~flags; /* turn flags off */
	//再设置回去
	if (fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
}