#include "apue.h"
#include <pthread.h>
//线程1的run
void * thr_fn1(void *arg) {
	printf("thread 1 returning\n");
	//正常返回
	return((void *)1);
}
//线程2的run
void * thr_fn2(void *arg) {
	printf("thread 2 exiting\n");
	//通过exit函数返回
	pthread_exit((void *)2);
}

//图11-3 获得线程退出状态
int main(void) {
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;//线程1的返回值
	//创建线程1
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		err_exit(err, "can't create thread 1");
	//创建线程2
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		err_exit(err, "can't create thread 2");
	//阻塞等待线程1,线程1终止的返回放到tret中
	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_exit(err, "can't join with thread 1");
	printf("thread 1 exit code (run return): %ld\n", (long)tret);
	//阻塞等待线程2,线程1终止的返回再放到tret中
	err = pthread_join(tid2, &tret);
	if (err != 0)
		err_exit(err, "can't join with thread 2");
	printf("thread 2 exit code (by pthread_exit): %ld\n", (long)tret);
	exit(0);
}
