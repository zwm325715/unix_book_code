#include "apue.h"
#include <pthread.h>

//图12-4 以分离状态创建线程
int makethread(void *(*fn)(void *), void *arg) {
	int				err;
	pthread_t		tid;
	pthread_attr_t	attr;
	//1.先初始化线程属性的默认值
	err = pthread_attr_init(&attr);
	if (err != 0)
		return(err);
	//2.再设置线程属性之"detachstate":以"分离状态"启动线程
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (err == 0)
		//3.然后创建线程，把属性对象作为第2个参数传入
		err = pthread_create(&tid, &attr, fn, arg);
	//释放线程属性的资源
	pthread_attr_destroy(&attr);
	return(err);
}
