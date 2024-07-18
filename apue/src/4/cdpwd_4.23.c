#include "apue.h"
// 图4-24:将工作目录更改至一个指定的目录，然后调用getcwd打印该工作目录
int main(void) {
	char	*ptr;
	size_t		size;
	//更改进程的工作目录到"/home/ob/cplus_ws"
	if (chdir("/home/ob/cplus_ws") < 0)
		err_sys("chdir failed");
	//给"路径名字符串"在堆上分配内存(当作getcwd的buf)
	ptr = path_alloc(&size);	/* our own function */
	//把"当前工作目录的绝对路径"放到ptr中
	if (getcwd(ptr, size) == NULL)
		err_sys("getcwd failed");

	printf("cwd(进程的当前工作目录) = %s\n", ptr);
	exit(0);
}
