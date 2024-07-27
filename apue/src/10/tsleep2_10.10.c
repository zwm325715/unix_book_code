#include "apue.h"

unsigned int	sleep2(unsigned int);
static void		sig_int(int);

//图10-9 在一个捕捉其他信号的程序调用sleep2
int main(void) {
	unsigned int	unslept;
	//设置SIGINT的信号handler为sig_int
	if (signal(SIGINT, sig_int) == SIG_ERR){
		err_sys("signal(SIGINT) error");
	}
	//调用sleep2_10.10.c的中sleep2实现
	printf("main---call sleep2 for 4s: %u\n", unslept);
	/*
	1.该函数内的SigAlarm信号会中断sig_int函数的执行，
	  导致sig_int没有执行完程序就结束了
	2.睡4S后产生SIGALARM，
	  在终端通过ctrl+c产生SIGINT信号，从而sig_int执行(超过4s)而被SIGALARM中断  
	*/
	unslept = sleep2(4);
	printf("main---sleep2 returned: %u\n", unslept);
	exit(0);
}

// SIGINT的信号handler
static void sig_int(int signo) {
	int	i, j;
	//通过volatile阻止了优化编译程序去除循环语句
	volatile int	k;
	/*
	 * Tune(/tjuːn/调整;调音) these loops to run for more than 4 seconds
	 * on whatever system this test program is run.
	 * 调整这些循环，使其在运行此测试程序的任何系统上运行超过4秒
	 */
	printf("\n***handler***sig_int starting\n");
	for (i = 0; i < 3000000; i++)
		for (j = 0; j < 40000; j++)
			k += i * j;
	printf("***handler***sig_int finished\n");
}