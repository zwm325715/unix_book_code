#include "apue.h"
#include <pthread.h>

//线程ID
pthread_t ntid;

void printids(const char *s) {
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();//进程ID
	//线程ID:不能使用ntid(因为main在赋该值之前线程就先运行了，此时就是空)
	tid = pthread_self();

	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
	  (unsigned long)tid, (unsigned long)tid);
}
//run函数
void * thr_fn(void *arg) {
	printids("new thread: ");
	return((void *)0);
}

//图11-2 打印线程ID
int main(void) {
	int		err;
	//创建具有默认属性的线程:run函数为thr_fn，不需要参数
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
		err_exit(err, "can't create thread");
	printids("main thread:");
	sleep(1);
	exit(0);
}
