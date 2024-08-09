#include "apue.h"
#include <fcntl.h>

/*
	图14-5 加锁或解锁一个文件区域的函数
*/
int lock_reg(int fd, //文件描述符
			int cmd, //命令
			int type, //锁类型
			off_t offset, //字节偏移量，相对于whence
			int whence, //文件位置
			off_t len/*区域字节长度*/) {
	struct flock	lock;
	/* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_type = type;
	/* byte offset, relative to l_whence */
	lock.l_start = offset;	
	/* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_whence = whence;	
	/* #bytes (0 means to EOF) */
	lock.l_len = len;
	//调用fcntl记录锁
	return(fcntl(fd, cmd, &lock));
}