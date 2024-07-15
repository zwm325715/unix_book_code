#include "apue.h"

/* 
	external variable in initialized data
	初始化数据段中的外部(全局)变量
 */
int		globvar = 6;
//字符串
char	buf[] = "a write to stdout\n";
//实例8-1演示了fork函数:
//  从中可以看到子进程对变量所做的改变并不影响父进程中该变量的值
int main(void) {
	/* automatic variable on the stack
		栈上的自动变量(局部变量)
	 */
	int		var;
	pid_t	pid;

	var = 88;
	/*
		1.写到到标准输出
			sizeof是包含尾零的，这里-1是去掉尾零(不是去掉'\n')
		2.write是系统调用，不带缓冲	
	*/	
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	/* we don't flush stdout 
	1.printf是标准I/O的函数，是带缓冲的
	2.没有显示调用flush来刷新标准输出缓冲区
		默认标准输出是行缓冲模式，buf有换行符，所以也会flush
	3.但是重定向到文件时，就变成全缓冲了
		在调用fork时,该行数据还在缓冲区中，
		然后在将父进程数据空间复制到子进程中，该缓冲区数据也被复制到子进程中.
		因此父子进程在进程终止时，该行数据都会写到文件中
	*/
	printf("before fork\n");	
	//创建子进程
	if ((pid = fork()) < 0) {//失败
		err_sys("fork error");
	} else if (pid == 0) {/* child 子进程走这里*/
		/*
			由于是COW写时复制，是副本因此不会影响父进程中的值:
				不管是全局还是局部变量
		*/
		sleep(5);
		/* modify variables 修改全局变量*/
		globvar++;
		//修改局部变量
		var++;
	} else {/* parent 父进程走这里*/
		//这里用的伪同步：让子进程先走完(不一定哦)
		//10.16节中，会使用信号使父子进程同步
		sleep(10);
	}
	/*
	父子进程都会执行打印语句:
	   一般是子进程先输出，不过不一定哦,还是依赖cpu调度，虽然主线程睡眠了2s
	*/
	printf("pid = %ld, glob = %d, var = %d\n", 
			(long)getpid(), globvar, var);
	exit(0);
}
