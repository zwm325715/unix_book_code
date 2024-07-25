#include "apue.h"
#include <pwd.h>
#include <stdio.h>
//信号handler
static void my_alarm(int signo) {
	struct passwd *rootptr;//通常指向的是一个静态变量
	printf("in signal handler\n");
	//getpwnam好像不行，改成了getpwuid
	//调用"非可重入函数getpwnam()"去修改passwd的静态变量
	// if ((rootptr = getpwnam("ob")) == NULL) { //用书上的这行代码会永远阻塞
	if ((rootptr = getpwuid(0)) == NULL) {
		err_sys("getpwnam(root) error");
	}
	//定时器超时(1秒)就会产生SIGALRM信号.效果无限的在执行该函数
	alarm(1);
}
/*
	这段代码跟书上的不一样:
		书上在main和handler都是使用getpwnam函数，但是在linux上执行时
		由于该函数是不可重入的，所以linux会在该函数处永远阻塞住，不是无限的触发
*/
//图10-5 在信号处理程序中调用不可重入函数
int main(void) {
	struct passwd *ptr;
	//捕捉SIGALRM信号，调用my_alarm函数
	signal(SIGALRM, my_alarm);
	//首次触发SIGALRM信号
	alarm(1);
	//死循环:用来校验passwd的静态变量是否被修改了
	for ( ; ; ) {
		//这里要改成自己linux登录的用户名
		if ((ptr = getpwnam("ob")) == NULL) {
			err_sys("getpwnam error");
		}
		//用户名不是ob时
		if (strcmp(ptr->pw_name/*用户名*/, "ob") != 0) {
			//(corrupted /kəˈrʌptɪd/ 损坏的)
			printf("return value corrupted!, pw_name = %s\n",
					ptr->pw_name);
		}
	}
}
