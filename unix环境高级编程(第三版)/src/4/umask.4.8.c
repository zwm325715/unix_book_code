#include "apue.h"
#include <fcntl.h>

//rw-rw-rw-
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
//图4-9:创建2个文件"文件模式创建屏蔽字"
int main(void) {
	//1.不做任何屏蔽
	umask(0);
	if (creat("foo", RWRWRW) < 0)//创建文件foo:使用宏mode
		err_sys("creat error for foo");
	//2.屏蔽"所有组读写，其他用户读写"	
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0)//创建文件bar:使用宏mode
		err_sys("creat error for bar");
	exit(0);
}
