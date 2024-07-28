#include "apue.h"
#include <setjmp.h>
#include <stdio.h>
#include <time.h>

static void						sig_usr1(int);
static void						sig_alrm(int);
static sigjmp_buf				jmpbuf;
/*
sig_atomic_t数据类型:
1.在写这种类型变量时不会被中断.
  这意味着在具有虚拟存储器的系统上,这种变量不会跨越页边界，
  可以用一条机器指令对其进行访问
2.这种类型的变量总是包括修饰符volatile,原因是
  该变量由2个不同的控制线程-main函数和异步执行的handler访问
*/
static volatile sig_atomic_t	canjump;

//图10-20 信号屏蔽、sigsetjmp和siglongjmp实例
int main(void) {
	//设置SIGUSR1的handler为sig_usr1函数
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	//设置SIGALRM的handler为sig_alrm函数	
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");
	/* {Prog prmask} */
	// 打印进程的当前信号屏蔽字
	pr_mask("===starting main: ");		
	/*
	设置信号handler的非局部jmp点,
	参数savemask非0(1),因此会保存进程的当前信号屏蔽字
	*/
	if (sigsetjmp(jmpbuf, 1)) {//siglongjmp回来时进入
		pr_mask("---main---ending main print_mask: ");
		exit(0);
	}
	/* 
	now sigsetjmp() is OK 
	信号handler会检测此变量:
		仅当canjump为非0时才调用siglongjmp,
		是一种保护机制(防止没有sigsetjmp时就调用handler)
	*/
	canjump = 1;	
	for ( ; ; ) {
		printf("=== main:pause start!\n");
		pause();//暂停等信号
		printf("=== main:pause over,wake up!\n");
	}
}

/*
1.SIGUSR1的handler
2.当调用一个信号处理程序(handler)时,被捕捉的信号SIGUSR1会加到进程的当前信号屏蔽字中,
	当从信号处理程序(handler)返回时,恢复原来的屏蔽字
*/ 
static void sig_usr1(int signo) {
	time_t	starttime;
	//canjump为1(也就是sigsetjmp)后才接收处理SIGUSR1信号
	if (canjump == 0)
		return;		/* unexpected signal, ignore */
	// 打印进程的当前信号屏蔽字
	pr_mask("---starting sig_usr1 print_mask: ");
	/*
	定时器，3s后触发SIGALRM信号:
		也就是制造在执行handler时触发了其他的信号,
		SIGALRM信号会中断该handler的执行
	*/
	alarm(3);/* SIGALRM in 3 seconds */
	//取当前时间(距离UTC的秒数)
	starttime = time(NULL);
	/* busy wait for 5 seconds 忙等5s*/
	for ( ; ; )	{
		//死循环5s钟后才退出循环
		if (time(NULL) > starttime + 5) {
			printf("sig_usr1 for loop 5s end \n");
			break;
		}
	}
	// 打印进程的当前信号屏蔽字
	pr_mask("---finishing sig_usr1 print_mask: ");
	//canjump置为0
	canjump = 0;
	/* 
		jump back to main, don't return 这里是跳转，不是返回
		跳回sigsetjmp标志点，并恢复由sigsetjmp保存的信号屏蔽字
	*/
	siglongjmp(jmpbuf, 1);	
}

/*
1.SIGALRM的handler
2.当调用一个信号处理程序(handler)时,被捕捉的信号(SIGALRM)会加到进程的当前信号屏蔽字中,
	当从信号处理程序(handler)返回时,恢复原来的屏蔽字
*/ 
static void sig_alrm(int signo) {
	time_t	starttime;
	starttime = time(NULL);
	// 打印进程的当前信号屏蔽字
	pr_mask("~~~in sig_alrm print_mask: ");
	for ( ; ; )	{
		//死循环10s钟后才退出循环
		if (time(NULL) > (starttime + 10)) {
			printf("sig_alrm for loop 10s end \n");
			break;
		}
	}
	printf("~~~sig_alrm handler end!\n");
}
