#include "apue.h"
#include <pthread.h>
#include <stdio.h>

//线程退出时的清理handler
void cleanup(void *arg) {
	printf("cleanup: %s\n", (char *)arg);
}

//线程1的run函数:通过return关键字返回
void * thr_fn1(void *arg) {
	printf("thread 1 start\n");
	//清理handler入栈，并传递参数
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg) {
		printf("thread 1 arg not null,return 1\n");
		/*如果是从run中使用return关键字返回时，它的清理handler就不会被调用*/
		return((void *)1);
	}
	printf("thread 1 start pop cleanup handler\n");
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	printf("thread 1 end pop cleanup handler\n");
	return((void *)1);
}
//线程2的run函数:通过pthread_exit返回
void * thr_fn2(void *arg) {
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg) {
		printf("thread 2 arg not null,pthread_exit(2)\n");
		/*
		使用pthread_exit退出时就会调用清理handler
		*/
		pthread_exit((void *)2);
	}
	printf("thread 2 start pop cleanup handler\n");
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	printf("thread 2 end pop cleanup handler\n");
	pthread_exit((void *)2);
}

int main(void) {
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;
	//创建线程1:run为thr_fn1，参数为1
	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
		err_exit(err, "can't create thread 1");
	//创建线程2:run为thr_fn2，参数为1	
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if (err != 0)
		err_exit(err, "can't create thread 2");
	
	//阻塞等待线程1的返回
	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_exit(err, "can't join with thread 1");
	//打印返回值
	printf("main join: thread 1 exit code %ld\n", (long)tret);

	//阻塞等待线程2的返回
	err = pthread_join(tid2, &tret);
	if (err != 0)
		err_exit(err, "can't join with thread 2");
	//打印返回值	
	printf("main join: thread 2 exit code %ld\n", (long)tret);
	exit(0);
}
