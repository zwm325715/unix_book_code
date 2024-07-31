#include <stdlib.h>
#include <pthread.h>
//图11-10 使用互斥量保护数据结构
struct foo {
	int             f_count;
	//互斥量
	pthread_mutex_t f_lock;
	int             f_id;
	/* ... more stuff here 更多的东西这里 ... */
};
/* allocate the object */
struct foo * foo_alloc(int id) {
	struct foo *fp;

	if ((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		fp->f_id = id;
		//使用默认属性对互斥量初始化
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return(NULL);
		}
		/* ... continue initialization ... */
	}
	return(fp);
}

/* add a reference to the object */
void foo_hold(struct foo *fp) {
	//加锁
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	//解锁
	pthread_mutex_unlock(&fp->f_lock);
}
/* release a reference to the object */
void foo_rele(struct foo *fp) {
	//加锁
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0) { /* last reference */
		//解锁
		pthread_mutex_unlock(&fp->f_lock);
		//destroy互斥量
		pthread_mutex_destroy(&fp->f_lock);
		//释放内存
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}
