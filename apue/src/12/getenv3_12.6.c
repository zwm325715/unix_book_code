#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRINGSZ	4096
//线程私有数据键
static pthread_key_t key;
//pthread_once的静态变量
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
//互斥量
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;
//线程初始化(只执行1次)
static void thread_init(void) {
	/**
	创建"线程私有数据键":
	  析构函数为释放内存的free函数，来释放malloc分配的内存
	  只有当私有数据值非空时，析构函数free才会被调用
	*/
	pthread_key_create(&key, free);
}
/*
	图12-13 线程安全的getenv的兼容版本，但不是异步信号安全的
*/
char *getenv(const char *name) {
	int		i, len;
	char	*envbuf;
	//只执行1次:确保只创建一个键
	pthread_once(&init_done, thread_init);
	//加锁
	pthread_mutex_lock(&env_mutex);
	//*****************核心逻辑*****************
	//获得"线程私有数据"的地址
	envbuf = (char *)pthread_getspecific(key);
	//没有数据时(有就直接使用了)
	if (envbuf == NULL) {
		//堆中分配内存，数据地址指向起始位置
		envbuf = malloc(MAXSTRINGSZ);
		//内存分配失败时
		if (envbuf == NULL) {
			//解锁
			pthread_mutex_unlock(&env_mutex);
			return(NULL);
		}
		//把"键"和"线程私有数据"关联起来
		pthread_setspecific(key, envbuf);
	}
	//环境变量key的长度
	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++) {
		//匹配入参，并且key后面的字符是'='
		if ((strncmp(name, environ[i], len) == 0) &&
		  (environ[i][len] == '=')) {
			//把环境变量key对应的值(从'='后开始的字符，碰到尾零为止)复制到envbuf字符数组中
			strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
			//解锁
			pthread_mutex_unlock(&env_mutex);
			return(envbuf);
		}
	}
	//没有找到时，也解锁，并返回null
	pthread_mutex_unlock(&env_mutex);
	return(NULL);
}
