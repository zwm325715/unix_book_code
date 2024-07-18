#include "apue.h"
#include <fcntl.h>
//图4-16:打开一个文件，然后unlink它
int main(void) {
	/*
		1.打开一个文件(4.8节创建的文件):读写
		2.bar文件的权限如下
		-rw-r--r-- 1(硬链接计数) ob ob  0 Jul  7 02:11 bar
	*/
	if (open("bar", O_RDWR) < 0)
		err_sys("open error");
	//删除一个目录项(解除硬链接)
	if (unlink("bar") < 0)
		err_sys("unlink error");
	//此时不能通过ls -l bar来查看这个文件，提示no such file
	//但是，磁盘空间还没有释放，直到整个进程结束才释放.
	printf("file unlinked\n");
	sleep(15);//睡眠15秒
	printf("done\n");
	exit(0);
}
