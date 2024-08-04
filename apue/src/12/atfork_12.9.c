#include "apue.h"
#include <pthread.h>

//2个互斥量
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
//pthread_atfork的prepare函数:用于获取父进程定义的所有锁
void prepare(void) {
	int err;

	printf("preparing locks...\n");
	//对2个互斥量进行加锁
	if ((err = pthread_mutex_lock(&lock1)) != 0)
		err_cont(err, "can't lock lock1 in prepare handler");
	if ((err = pthread_mutex_lock(&lock2)) != 0)
		err_cont(err, "can't lock lock2 in prepare handler");
}
//pthread_atfork的parent函数:用于对prepare获取的所有锁进行解锁
void parent(void) {
	int err;

	printf("parent unlocking locks...\n");
	//解锁
	if ((err = pthread_mutex_unlock(&lock1)) != 0)
		err_cont(err, "can't unlock lock1 in parent handler");
	if ((err = pthread_mutex_unlock(&lock2)) != 0)
		err_cont(err, "can't unlock lock2 in parent handler");
}
//pthread_atfork的child函数:用于对prepare获取的所有锁进行解锁
void child(void) {
	int err;

	printf("child unlocking locks...\n");
	//解锁
	if ((err = pthread_mutex_unlock(&lock1)) != 0)
		err_cont(err, "can't unlock lock1 in child handler");
	if ((err = pthread_mutex_unlock(&lock2)) != 0)
		err_cont(err, "can't unlock lock2 in child handler");
}
//线程的run函数
void * thr_fn(void *arg) {
	printf("thread started...\n");
	//暂停等信号
	pause();
	return(0);
}

//图12-17 pthread_atfork实例
int main(void) {
	int			err;
	pid_t		pid;
	pthread_t	tid;
	//要求以清除锁状态的形式去fork子进程
	if ((err = pthread_atfork(prepare, parent, child)) != 0)
		err_exit(err, "can't install fork handlers");
	//创建一个线程	
	if ((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0)
		err_exit(err, "can't create thread");
	//睡2秒
	sleep(2);
	printf("parent about to fork...\n");
	//创建一个子进程
	if ((pid = fork()) < 0)
		err_quit("fork failed");
	else if (pid == 0)	/* child 子进程执行*/
		printf("child returned from fork\n");
	else		/* parent 父进程执行*/
		printf("parent returned from fork\n");
	exit(0);
}
