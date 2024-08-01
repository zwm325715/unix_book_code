#include "apue.h"
#include <pthread.h>

//图11-13 使用pthread_mutex_timedlock
int main(void) {
	int err;
	struct timespec tout;
	struct tm *tmp;
	char buf[64];
	//互斥量静态初始化
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	//加锁
	pthread_mutex_lock(&lock);
	printf("mutex is locked\n");
	//取当前系统实时时间(日历时间),放到tout中
	clock_gettime(CLOCK_REALTIME, &tout);
	//日历时间tout转成本地时间并分解 放到tmp中
	tmp = localtime(&tout.tv_sec);
	//格式化:本地时间(12小时制,没有日期),放到buf中
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("current time is %s\n", buf);
	//加10S
	tout.tv_sec += 10;	/* 10 seconds from now */
	/* 
		caution: this could lead to deadlock
		注意:这可能导致死锁(同一线程再次申请超时加锁)
	 */
	err = pthread_mutex_timedlock(&lock, &tout);
	//再取时间，同上再打印出来
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("the time is now %s\n", buf);
	//可重入锁
	if (err == 0)
		printf("mutex locked again!\n");
	else
		//不可重入锁
		printf("can't lock mutex again:%d - %s\n",err,strerror(err));
	exit(0);
}
