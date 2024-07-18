#include "apue.h"

static void	my_exit1(void);
static void	my_exit2(void);

// 图7-3:如何使用atexit函数
int main(void) {
	//注册"终止处理程序":my_exit2
	if (atexit(my_exit2) != 0)
		err_sys("can't register my_exit2");
	//注册"终止处理程序":my_exit1
	if (atexit(my_exit1) != 0)
		err_sys("can't register my_exit1");
	//重复注册"终止处理程序":my_exit1			
	if (atexit(my_exit1) != 0)
		err_sys("can't register my_exit1");
	
	printf("main is done\n");
	//注册顺序和执行顺心是相反的，可重复注册结果就是被重复调用
	//因此调用顺序为my_exit1->my_exit1->my_exit2
	// return(0);
	exit(0);
}

static void my_exit1(void) {
	printf("first exit handler\n");
}

static void my_exit2(void) {
	printf("second exit handler\n");
}
