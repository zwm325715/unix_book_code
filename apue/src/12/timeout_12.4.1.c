#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
// 使用detach_12.3.c中实现：以分离状态创建线程
extern int makethread(void *(*)(void *), void *);

//结构体
struct to_info {
	/* function */
	void  (*to_fn)(void *);
	/* argument */
	void * to_arg;
	/* time to wait 还需要等待的相对时间*/
	struct timespec to_wait;
};
/* seconds to nanoseconds  1S等于多少纳秒*/
#define SECTONSEC  1000000000	

// 没有"系统实时时间"宏 或 定义了"BSD"宏时  (linux不满足该条件)
#if !defined(CLOCK_REALTIME) || defined(BSD)
#define clock_nanosleep(ID, FL, REQ, REM)	nanosleep((REQ), (REM))
#endif
// 没有"系统实时时间"宏时(linux不满足)
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#define USECTONSEC 1000		/* microseconds to nanoseconds */

void clock_gettime(int id, struct timespec *tsp) {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	tsp->tv_sec = tv.tv_sec;
	tsp->tv_nsec = tv.tv_usec * USECTONSEC;
}
#endif /*ifndef CLOCK_REALTIME*/

//线程run函数，接收to_info对象作为参数
void * timeout_helper(void *arg) {
	struct to_info	*tip;
	//拿到参数对象
	tip = (struct to_info *)arg;
	//线程在时间未到时将一直等待，时间到了以后再调用请求的函数
	//睡眠to_wait相对时间(秒+纳秒)，使用了更高精度的休眠
	clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
	//执行函数:本示例也就是retry
	(*tip->to_fn)(tip->to_arg);
	free(arg);//释放内存
	return(0);
}

/*
	该函数允许安排另一个函数在未来的某个时间运行
	创建"分离线程"并把"计算的相对超时时间放到to_info对象"中作为run函数的参数
*/
void timeout(const struct timespec *when, void (*func)(void *), void *arg) {
	struct timespec	now;
	struct to_info	*tip;
	int				err;
	//当前时间
	clock_gettime(CLOCK_REALTIME, &now);
	//未超时(先比秒数，再比纳秒)时
	if ((when->tv_sec > now.tv_sec) ||
	  (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)) {
		//分配to_info对象的内存
		tip = malloc(sizeof(struct to_info));
		if (tip != NULL) {
			//把入参放进去
			tip->to_fn = func;
			tip->to_arg = arg;
			//还需要等待几秒
			tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
			//超时时的纳秒维度大时
			if (when->tv_nsec >= now.tv_nsec) {
				//设置超时纳秒相对时间
				tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
			} else {//否则
				//相对秒数-1
				tip->to_wait.tv_sec--;
				//计算等待的相对纳秒数
				tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec +
				  when->tv_nsec;
			}
			//创建线程，把to_info对象传过去
			err = makethread(timeout_helper, (void *)tip);
			if (err == 0)
				return;
			else
				free(tip);//失败时释放内存
		}
	}

	/*
	 * We get here if (a) when <= now, or (b) malloc fails, or
	 * (c) we can't make a thread, so we just call the function now.
	 */
	(*func)(arg);
}

//互斥量的属性
pthread_mutexattr_t attr;
//互斥量
pthread_mutex_t mutex;

//超时后执行的函数
void retry(void *arg) {
	pthread_mutex_lock(&mutex);//加锁

	/* perform retry steps ... */

	pthread_mutex_unlock(&mutex);//解锁
}
//图12-8 使用递归互斥量
int main(void) {
	int	err, condition, arg;
	struct timespec	when;
	//初始互斥量属性
	if ((err = pthread_mutexattr_init(&attr)) != 0)
		err_exit(err, "pthread_mutexattr_init failed");
	//修改"类型属性"为递归
	if ((err = pthread_mutexattr_settype(&attr,
	  						PTHREAD_MUTEX_RECURSIVE)) != 0)
		err_exit(err, "can't set recursive type");
	//使用"属性attr对象"初始化"互斥量mutex"
	if ((err = pthread_mutex_init(&mutex, &attr)) != 0)
		err_exit(err, "can't create recursive mutex");

	/* continue processing ... */
	pthread_mutex_lock(&mutex);//加锁
	/*
	 * Check the condition under the protection of a lock to
	 * make the check and the call to timeout atomic.
	  检查锁保护下的条件，使检查和对timeout的调用成为原子性的.
	 */
	if (condition) {
		/*
		 * Calculate the absolute time when we want to retry.
		 	计算想要重试的绝对时间.
		 */
		clock_gettime(CLOCK_REALTIME, &when);
		/* 10 seconds from now  10秒后的绝对时间*/
		when.tv_sec += 10;	
		//调用timeout函数
		timeout(&when, retry, (void *)((unsigned long)arg));
	}
	pthread_mutex_unlock(&mutex);

	/* continue processing ... */
	exit(0);
}
