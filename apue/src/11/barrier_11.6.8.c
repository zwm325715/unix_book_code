#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

//图11-16 使用屏障

#define NTHR   8				/* number of threads */
#define NUMNUM 8000000L			/* number of numbers to sort */
#define TNUM   (NUMNUM/NTHR)	/* number to sort per thread */

long nums[NUMNUM];//原始数组
long snums[NUMNUM];//排序后的数组
//屏障变量
pthread_barrier_t b;

#ifdef SOLARIS
#define heapsort qsort
#else
// 要自己实现堆排序，这里暂时不提供排序实现了。主要知道这个思想即可
extern int heapsort(void *, size_t, size_t,
                    int (*)(const void *, const void *));
#endif

/*
 * Compare two long integers (helper function for heapsort)
 */
int complong(const void *arg1, const void *arg2) {
	long l1 = *(long *)arg1;
	long l2 = *(long *)arg2;

	if (l1 == l2)
		return 0;
	else if (l1 < l2)
		return -1;
	else
		return 1;
}

/*
 * Worker thread to sort a portion(/ˈpɔːʃ(ə)n/ 一部分) of the set of numbers.
 * 工作线程对数字集的一部分进行排序
 */
void * thr_fn(void *arg) {
	long	idx = (long)arg;

	heapsort(&nums[idx], TNUM, sizeof(long), complong);
	//等待排序完
	pthread_barrier_wait(&b);

	/*
	 * Go off and perform more work ...
	 */
	return((void *)0);
}

/*
 * Merge the results of the individual sorted ranges.
 * 合并各个排序范围的结果:一个有趣的拆分合并思想
 */
void merge() {
	long	idx[NTHR];
	long	i, minidx, sidx, num;
	/*
		首先merge的初始条件：连续存放数据的超长数组，0~999999, 1000000~1999999, ...
		每一段都是已排序好的数；idx[0]，idx[1]...
		初始指向8段数字的第一个数的位置（也就是每段最小的数）
	*/
	for (i = 0; i < NTHR; i++)	
		idx[i] = i * TNUM;//每个线程对应的数据在原始数组中的下标
	/*
	 思路：
	 	想象有8个游标，分别指向这8段，每次循环从8段中找到最小的数,
		最小的数所在的段的游标移动到下一个数，其他段的游标则不动
	步骤：	
   		1.每轮拿出8段中的8个idx[]指向的最小的数，
		 并将该段指向位置后移一位(也就是开始时idx[i]保存的是该段最小值的位置，那么把该最小值取出后，idx[i]++)；
		2.把每次取出的值依次放在snums数组中，snums长度和nums长度相等。
		3.最终snums就是排序结果。
	*/

	//遍历原数据	
	for (sidx = 0; sidx < NUMNUM; sidx++) {
		num = LONG_MAX;
		//找到最小的那个
		for (i = 0; i < NTHR; i++) {
			if ((idx[i] < (i+1)*TNUM) /*位置约束：第i段中idx[i]指向的位置还在下一段初始位置之前*/
				&& (nums[idx[i]] < num)/*最小数约束：当前位置的数小于已求得的最小数*/) {
				num = nums[idx[i]];//将最小的数给num
				minidx = i;// 将最小的段号给minidx
			}
		}
		// 将本轮8个数求得的最小数给snums[sidx]
		snums[sidx] = nums[idx[minidx]];
		// 将最小数那一段idx指向的位置后挪一位
		idx[minidx]++;
	}
}

int main() {
	unsigned long	i;
	struct timeval	start, end;
	long long		startusec, endusec;
	double			elapsed;
	int				err;
	pthread_t		tid;

	/*
	 * Create the initial set of numbers to sort.
	 */
	srandom(1);//创建种子
	for (i = 0; i < NUMNUM; i++)
		nums[i] = random();//生成随机数

	/*
	 * Create 8 threads to sort the numbers.
	 */
	gettimeofday(&start, NULL);
	//初始化屏障(注意+1,原因main线程也调用wait)
	pthread_barrier_init(&b, NULL, NTHR+1);
	for (i = 0; i < NTHR; i++) {
		//创建线程，传了对应数据的开始坐标
		err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
		if (err != 0)
			err_exit(err, "can't create thread");
	}
	//等待8个线程完成
	pthread_barrier_wait(&b);
	merge();
	gettimeofday(&end, NULL);

	/*
	 * Print the sorted list.
	 */
	startusec = start.tv_sec * 1000000 + start.tv_usec;
	endusec = end.tv_sec * 1000000 + end.tv_usec;
	elapsed = (double)(endusec - startusec) / 1000000.0;
	printf("sort took %.4f seconds\n", elapsed);
	for (i = 0; i < NUMNUM; i++)
		printf("%ld\n", snums[i]);
	exit(0);
}
