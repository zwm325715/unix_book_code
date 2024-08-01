#include <pthread.h>

struct msg {
	struct msg *m_next;
	//更多的东西在这里
	/* ... more stuff here ... */
};

struct msg *workq;
//条件变量静态初始化
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
//互斥量静态初始化
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void) {
	struct msg *mp;

	for (;;) {
		//1.先锁住互斥量
		pthread_mutex_lock(&qlock);
		//通过while来重新计算条件(检查条件)
		while (workq == NULL) {
			//2.再等待条件变量变为真
			//  函数内会把互斥量qlock解锁
			pthread_cond_wait(&qready, &qlock);
			//  返回后再次解锁
		}
		mp = workq;//取到当前workq
		workq = mp->m_next;//把mp的next 给到 workq
		//解锁
		pthread_mutex_unlock(&qlock);
		/* 
			now process the message mp 
			接下来就可以处理这个mp对象了
		*/
	}
}

void enqueue_msg(struct msg *mp) {
	//1.先锁住互斥量
	pthread_mutex_lock(&qlock);
	//改变条件状态(头插法让对列非空)
	mp->m_next = workq;
	workq = mp;
	//2.在解锁
	pthread_mutex_unlock(&qlock);
	//3.至少唤醒一个等待该条件qready的线程
	//  给等待线程发信号时，不需要占有互斥量
	pthread_cond_signal(&qready);
}
