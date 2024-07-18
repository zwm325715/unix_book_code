#include "apue.h"
#include <setjmp.h>

static void	f1(int, int, int, int);
static void	f2(void);

static jmp_buf	jmpbuffer;
static int		globval;//全局变量
//图7-13:longjmp对各类变量的影响
int main(void) {
	int				autoval;//自动变量
	register int	regival;//寄存器变量
	volatile int	volaval;//易失变量
	static int		statval;//静态变量
	//赋值
	globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;
	//设置跳转点
	if (setjmp(jmpbuffer) != 0) {//longjmp回来后非0了
		//longjmp后再打印一下变量的值
		printf("after longjmp:\n");
		//这里利用了ISO C的多行字符串连接到一行的一个语法:"a" "b" 等价于 "ab"
		printf("globval = %d, autoval = %d, regival = %d,"
		    " volaval = %d, statval = %d\n",
		    globval, autoval, regival, volaval, statval);
		exit(0);
	}

	//在"setjmp后，longjmp前"更改变量的值
	globval = 95; autoval = 96; regival = 97; volaval = 98; statval = 99;
	//调用f1
	f1(autoval, regival, volaval, statval);	
	exit(0);
}

static void f1(int i, int j, int k, int l) {
	//longjmp前打印下一变量的值
	printf("in f1():\n");
	printf("globval = %d, autoval = %d, regival = %d,"
	    " volaval = %d, statval = %d\n", globval, i, j, k, l);
	f2();
}

static void f2(void) {
	//跳回去，返回1
	longjmp(jmpbuffer, 1);
}
