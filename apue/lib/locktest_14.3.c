#include "apue.h"
#include <fcntl.h>

//图14-6 测试一个锁条件的函数
pid_t lock_test(int fd, 
				int type, //锁类型
				off_t offset, //字节偏移量，相对于whence
				int whence, //文件位置
				off_t len/*区域字节长度*/) {
	//记录锁结构体
	struct flock	lock;
	//把参数挨着牌的放到结构体中
	/* F_RDLCK or F_WRLCK  只传这2种类型的锁
	  注意这里没有F_UNLCK:
	   因为在F_GETLK时如果不存在这个读锁/写锁时就会设置为F_UNLCK*/
	lock.l_type = type;	
	lock.l_start = offset;	/* byte offset, relative to l_whence */
	lock.l_whence = whence;	/* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len;		/* #bytes (0 means to EOF) */

	//使用F_GETLK命令去测试锁
	if (fcntl(fd, F_GETLK, &lock) < 0) //调用失败时
		err_sys("fcntl error");
	//当前这一时刻不存在一把锁
	if (lock.l_type == F_UNLCK) {
		/* 
			false, region isn't locked by another proc 
			请求的区域没有被另一个进程锁住
		*/
		return(0);
	}
	/* 
		true, return pid of lock owner 
		有锁，返回持有该锁的进程ID
	*/
	return(lock.l_pid);	
}
