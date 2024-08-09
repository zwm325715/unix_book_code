#include "apue.h"
#include <fcntl.h>
//锁1个字节
static void lockabyte(const char *name, int fd, off_t offset) {
	//相对文件头偏移offset字节，区域长度为1字节,进行阻塞(休眠)方式加独占式写锁
	if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
		err_sys("%s: writew_lock error", name);
	printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

/*
	图14-7 死锁检测实例：2个进程对同一文件加锁顺序不一样时就会死锁:
	检测到死锁时，内核必须选择一个进程接收出错返回
 		可以是父进程，也可以是子进程，由OS实现来决定
*/
int main(void) {
	int		fd;
	pid_t	pid;

	/*
	 * Create a file and write two bytes to it.
	 创建一个文件并且写2个字节给它
	 */
	if ((fd = creat("templock", FILE_MODE)) < 0)
		err_sys("creat error");
	//写2个字节
	if (write(fd, "ab", 2) != 2)
		err_sys("write error");
	//阻塞SIGUSR1和SIGUSR2 信号
	TELL_WAIT();
	printf("父进程pid=%d\n",getpid());
	//创建子进程
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {/* child */
		printf("子进程pid=%d\n",getpid());
		//文件阻塞加锁，偏移0字节
		lockabyte("child", fd, 0);
		//kill给父进程发SIGUSR2信号(父进程会阻塞该信号)
		TELL_PARENT(getppid());
		//进程挂起等信号
		WAIT_PARENT();
		//文件阻塞加锁，偏移1字节
		lockabyte("child", fd, 1);
	} else {/* parent */
		//父子进程都对同一文件阻塞加锁，偏移1字节
		lockabyte("parent", fd, 1);
		//kill给子进程发SIGUSR1信号(子进程会阻塞该信号)
		TELL_CHILD(pid);
		//进程挂起等信号
		WAIT_CHILD();
		//父子进程都对同一文件阻塞加锁，偏移0字节
		lockabyte("parent", fd, 0);
	}
	exit(0);
}
