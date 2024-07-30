#include "apue.h"
#include <pthread.h>

struct foo {
	int a, b, c, d;
};
//打印结构体信息
void printfoo(const char *s, const struct foo *fp) {
	printf("%s", s);
	printf("  structure at 0x%lx\n", (unsigned long)fp);
	printf("  foo.a = %d\n", fp->a);
	printf("  foo.b = %d\n", fp->b);
	printf("  foo.c = %d\n", fp->c);
	printf("  foo.d = %d\n", fp->d);
}
//thread1的run
void * thr_fn1(void *arg) {
	//栈上分配的结构体
	struct foo	foo = {1, 2, 3, 4};
	printfoo("thread 1:\n", &foo);
	//线程退出：返回的是栈上的对象
	pthread_exit((void *)&foo);
}
//thread2的run
void * thr_fn2(void *arg) {
	printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
	pthread_exit((void *)0);
}

//图11-4 pthread_exit参数的不正确使用
int main(void) {
	int			err;
	pthread_t	tid1, tid2;
	struct foo	*fp;
	//创建线程1
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		err_exit(err, "can't create thread 1");
	//阻塞等待线程终止，取返回值
	err = pthread_join(tid1, (void *)&fp);
	if (err != 0)
		err_exit(err, "can't join with thread 1");
	sleep(1);
	printf("parent starting second thread\n");
	//创建线程2
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		err_exit(err, "can't create thread 2");
	sleep(1);
	printfoo("parent:\n", fp);
	exit(0);
}
