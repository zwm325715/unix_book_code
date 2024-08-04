#include "apue.h"
#include <pthread.h>

int			quitflag;	/* set nonzero by thread */
//信号集
sigset_t	mask;
//互斥量
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//条件变量
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

//线程的run函数
void * thr_fn(void *arg) {
	//新建的线程会继承main的信号屏蔽字：阻塞SIGINT和SIGQUIT
	int err, signo;
	//死循环
	for (;;) {
		/*
		线程等待信号集mask中的一个或多个信号的发生:
			sigwait此时会解除信号SIGINT和SIGQUIT的阻塞状态
			也就是只有该线程可用于这2个信号的接收,其他线程不行
		*/
		err = sigwait(&mask, &signo/*对应的信号编号*/);
		if (err != 0)
			err_exit(err, "sigwait failed");
		//判断发生了什么信号
		switch (signo) {
			//中断信号
			case SIGINT:
				printf("\ninterrupt\n");
				break;
			//退出信号
			case SIGQUIT:
				pthread_mutex_lock(&lock);//加锁
				quitflag = 1;//变更值
				pthread_mutex_unlock(&lock);//解锁
				//至少唤醒一个等待该条件quitflag的线程
				pthread_cond_signal(&waitloc);
				return(0);

			default:
				printf("unexpected signal %d\n", signo);
				exit(1);
		}
	}
}
//图12-16 同步信号处理
int main(void) {
	int			err;
	sigset_t	oldmask;
	pthread_t	tid;
	//清空信号集mask
	sigemptyset(&mask);
	//往信号集添加2个信号SIGINT和SIGQUIT
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	//把信号集mask添加到线程的信号屏蔽字中：开始阻塞SIGINT和SIGQUIT
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
		err_exit(err, "SIG_BLOCK error");
	//创建线程
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0)
		err_exit(err, "can't create thread");
	//互斥量加锁(条件变量需要锁保护)
	pthread_mutex_lock(&lock);
	while (quitflag == 0) {
		//等待条件变量waitloc变为真(释放互斥量，等待条件的发生)
		pthread_cond_wait(&waitloc, &lock);
	}
	//解锁	
	pthread_mutex_unlock(&lock);

	/* 
	SIGQUIT has been caught and is now blocked; do whatever 
	SIGQUIT被捕获 并且现在是阻塞状态
	*/
	quitflag = 0;

	/* reset signal mask which unblocks SIGQUIT */
	//恢复旧的信号屏蔽字
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
	exit(0);
}
