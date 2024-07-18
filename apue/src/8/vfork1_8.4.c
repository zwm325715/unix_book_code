#include "apue.h"

int		globvar = 6;		
//图8-3:用vfork代替了fork
int main(void) {
	int		var;
	pid_t	pid;

	var = 88;
	//标准输出默认行缓冲，这里有换行符，因此会直接输出
	printf("before vfork\n");	
	/*
	产生新进程:
		父进程不需要sleep，因为vfork保证了在子进程
		调用exec或exit之前，内核会使父进程处于休眠状态
	*/
	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) {/* child 子进程执行的代码 */
		/* modify parent's variables 
		此时注意修改了父进程的内存空间的数据(影响了父进程的数据)
		*/
		globvar++;				
		var++;
		/* child terminates 子进程退出*/
		_exit(0);				
	}
	//子进程退出后，父进程继续执行
	/* parent continues here */
	//这里的打印的数据被子进程修改了
	printf("pid = %ld, glob = %d, var = %d\n", 
		(long)getpid(), globvar, var);
	exit(0);
}
