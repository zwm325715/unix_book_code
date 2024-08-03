#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

extern char **environ;
//互斥量
pthread_mutex_t env_mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;
//线程初始化(只被调用1次)
static void thread_init(void) {
	//互斥量属性
	pthread_mutexattr_t attr;
	//属性初始化
	pthread_mutexattr_init(&attr);
	//可重入类型属性
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	//互斥量初始化
	pthread_mutex_init(&env_mutex, &attr);
	//属性对象资源释放
	pthread_mutexattr_destroy(&attr);
}
/*
	图12-12 getenv的可重入(线程安全)版本
	1.调用者提供了自己的缓冲区来避免其他线程的干扰
	  还提供了锁
*/
int getenv_r(const char *name, char *buf, int buflen) {
	int i, len, olen;
	//保证不管多少线程同时竞争getenv_r，进程只调用thread_init函数1次
	pthread_once(&init_done, thread_init);
	len = strlen(name);
	//互斥量加锁
	pthread_mutex_lock(&env_mutex);
	for (i = 0; environ[i] != NULL; i++) {
		if ((strncmp(name, environ[i], len) == 0) &&
		  (environ[i][len] == '=')) {
			olen = strlen(&environ[i][len+1]);
			if (olen >= buflen) {
				//解锁
				pthread_mutex_unlock(&env_mutex);
				return(ENOSPC);
			}
			strcpy(buf, &environ[i][len+1]);
			//解锁
			pthread_mutex_unlock(&env_mutex);
			return(0);
		}
	}
	//解锁			
	pthread_mutex_unlock(&env_mutex);
	return(ENOENT);
}
