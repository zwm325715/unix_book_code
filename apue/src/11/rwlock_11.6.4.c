#include <stdlib.h>
#include <pthread.h>

//图11-14 使用读写锁
//任务
struct job {
	struct job *j_next;//后一个任务
	struct job *j_prev;//前一个任务
	/* 
	tells which thread handles this job
	告诉哪个线程处理此任务
	 */
	pthread_t   j_id;
	/*...more stuff here 更多的东西在这里...*/
};

//队列
struct queue {
	//只指向job链表的头(链表每个元素的连接关系交给job对象自己维护)
	struct job      *q_head;
	//只指向job链表的尾
	struct job      *q_tail;
	//读写锁
	pthread_rwlock_t q_lock;
};

/*
 * Initialize a queue. 初始化1个队列
 */
int queue_init(struct queue *qp) {
	int err;

	qp->q_head = NULL;
	qp->q_tail = NULL;
	//读写锁初始化，使用默认属性
	err = pthread_rwlock_init(&qp->q_lock, NULL);
	if (err != 0)
		return(err);
	/* ... continue initialization ... */
	return(0);
}

/*
 * Insert a job at the head of the queue.
 * 队列头部插入一个任务
 */
void job_insert(struct queue *qp, struct job *jp) {
	//写模式锁定
	pthread_rwlock_wrlock(&qp->q_lock);
	//1.新job对象的链表关系维护
	jp->j_next = qp->q_head; //"新job对象的next" 置为 "当前队列头(旧)"
	jp->j_prev = NULL;//"新job对象的prev"置空      
	//2.queue队列的job链表头和尾维护
	if (qp->q_head != NULL) {//头非空
		//"当前队列头的任务job对象(旧)的prev" 指向 "新的job对象"
		qp->q_head->j_prev = jp;
	}else {//头空
		/* list was empty */
		qp->q_tail = jp;//放尾
	}
	//"新来的job对象"放"queue的头部"
	qp->q_head = jp;
	//解锁
	pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Append a job on the tail of the queue.
 * 在队列尾部追加一个job
 */
void job_append(struct queue *qp, struct job *jp) {
	//写模式锁定
	pthread_rwlock_wrlock(&qp->q_lock);
	//1.新job对象的链表关系维护
	jp->j_next = NULL;//"新job对象的next" 置为 NULL
	jp->j_prev = qp->q_tail;//"新job对象的prev"置为 "链表的尾job"
	//2.queue队列的job链表头和尾维护
	if (qp->q_tail != NULL) { //队尾非空
		//"当前队列尾的任务job对象(旧)的next" 指向 "新的job对象"
		qp->q_tail->j_next = jp;
	} else {//尾空
		/* list was empty */
		qp->q_head = jp;//放头
	}
	//"新来的job对象"放"queue的尾部"
	qp->q_tail = jp;
	//解锁
	pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Remove the given job from a queue.
 * 从队列中移除一个job
 */
void job_remove(struct queue *qp, struct job *jp) {
	//写模式锁定
	pthread_rwlock_wrlock(&qp->q_lock);
	//该job任务在队列头
	if (jp == qp->q_head) {
		//1."queue的头" 变为 "删除job任务的next"
		qp->q_head = jp->j_next;
		//"删除job任务" 也是 "队queue列尾"
		if (qp->q_tail == jp) {
			//queue尾置空
			qp->q_tail = NULL;
		} else {//否则
			//2."删除job任务的next的prev"变为"删除job任务的prev"
			jp->j_next->j_prev = jp->j_prev;
		}			
	} else if (jp == qp->q_tail) {//该job任务在队列尾
		//1."queue的尾" 变为 "删除job任务的prev"
		qp->q_tail = jp->j_prev;
		//"删除job任务的prev的next" 变为 "删除job任务的next"
		jp->j_prev->j_next = jp->j_next;
	} else {//在中间
		//"待删除job任务"的处理
		jp->j_prev->j_next = jp->j_next;
		jp->j_next->j_prev = jp->j_prev;
	}
	pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Find a job for the given thread ID.
 * 用给定的线程ID去找一个任务:可并发
 */
struct job * job_find(struct queue *qp, pthread_t id) {
	struct job *jp;
	//读模式加锁
	if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
		return(NULL);
	//遍历查找
	for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
		if (pthread_equal(jp->j_id, id))
			break;
	//解锁
	pthread_rwlock_unlock(&qp->q_lock);
	return(jp);
}
