#include <stdlib.h>
#include <pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)
//散列表
struct foo *fh[NHASH];
//互斥量hashlock初始化
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
	int             f_count;
	//结构体里的互斥量
	pthread_mutex_t f_lock;
	int             f_id;
	struct foo     *f_next; /* protected by hashlock */
	/* ... more stuff here ... */
};

/* allocate the object */
struct foo * foo_alloc(int id) {
	struct foo	*fp;
	int			idx;

	if ((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		fp->f_id = id;
		//初始化结构体内的互斥量f_lock
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return(NULL);
		}
		idx = HASH(id);
		//先加锁互斥量hashlock
		pthread_mutex_lock(&hashlock);
		//往链表头添加
		fp->f_next = fh[idx];//先取出来
		fh[idx] = fp;//放链表头
		//再加锁互斥量f_lock
		pthread_mutex_lock(&fp->f_lock);
		//解锁hashlock
		pthread_mutex_unlock(&hashlock);
		/* ... continue initialization ... */
		//解锁f_lock
		pthread_mutex_unlock(&fp->f_lock);
	}
	return(fp);
}

/* add a reference to the object */
void foo_hold(struct foo *fp) {
	//再锁f_lock
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

/* find an existing object */
struct foo * foo_find(int id) {
	struct foo	*fp;
	//先锁hashlock
	pthread_mutex_lock(&hashlock);
	for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
		if (fp->f_id == id) {
			foo_hold(fp);
			break;
		}
	}
	pthread_mutex_unlock(&hashlock);
	return(fp);
}

/* release a reference to the object */
void foo_rele(struct foo *fp) {
	struct foo	*tfp;
	int			idx;
	//先锁f_lock
	pthread_mutex_lock(&fp->f_lock);
	if (fp->f_count == 1) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);
		//再锁hashlock
		pthread_mutex_lock(&hashlock);
		//又锁f_lock
		pthread_mutex_lock(&fp->f_lock);
		/* need to recheck the condition */
		if (fp->f_count != 1) {
			fp->f_count--;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return;
		}
		/* remove from list */
		idx = HASH(fp->f_id);
		tfp = fh[idx];
		if (tfp == fp) {
			fh[idx] = fp->f_next;
		} else {
			while (tfp->f_next != fp)
				tfp = tfp->f_next;
			tfp->f_next = fp->f_next;
		}
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	} else {
		fp->f_count--;
		pthread_mutex_unlock(&fp->f_lock);
	}
}
