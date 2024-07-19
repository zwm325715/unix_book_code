#include "apue.h"
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>
void checktime(char *str);

unsigned long long count;
struct timeval end;
//图8-30 更改nice值的效果(最好在单核cpu上运行效果才显著)
int main(int argc, char *argv[]) {
	pid_t	pid;
	char	*s;
	int		nzero, ret,nice0_child,nice0_parent;
	int		adj = 0;
	//关闭标准输出缓冲
	setbuf(stdout, NULL);
	//nzero赋值
#if defined(NZERO)//linux true
	nzero = NZERO;//默认nice值
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);//没有NZERO时通过sysconf取
#else
#error NZERO undefined
#endif
	//打印
	printf("NZERO = %d\n", nzero);
	if (argc == 2)
		//第1个参数字符串转换为整数
		adj = strtol(argv[1], NULL/*忽略非法部分*/, 10/*10进制*/);
	//取得日历时间(到微秒级),放到全局变量end中
	gettimeofday(&end, NULL);
	/* run for 10 seconds 运行10s*/
	end.tv_sec += 10;//往后10s
	//创建子进程
	if ((pid = fork()) < 0) {
		err_sys("fork failed");
	} else if (pid == 0) {/* child 子进程执行*/
		s = "child";
		//默认的nice值
		nice0_child = nice(0);
		printf("---nice0_child=%d,"
			"current nice value in child is %d, "
			"adjusting by %d\n",
			nice0_child,
			nice0_child+nzero,
			adj);
		//清除errno  
		errno = 0;
		//更改nice值
		if ((ret = nice(adj)) == -1 && errno != 0)//nice调用失败
			err_sys("---child set scheduling priority");
		printf("---ret=%d\n",ret);
		//新的nice值	
		printf("---now child nice value is %d\n", ret+nzero);
	} else {/* parent 父进程执行的代码*/
		s = "parent";
		nice0_parent = nice(0);
		printf("nice0_parent=%d,current nice value in parent is %d\n",
			 nice0_parent,
			 nice0_parent+nzero);
	}
	//循环直到时间到了
	for(;;) {
		if (++count == 0)//自增1
			err_quit("%s counter wrap", s);
		checktime(s);
	}
}

//检查时间
void checktime(char *str) {
	struct timeval	tv;
	//取当前日历
	gettimeofday(&tv, NULL);
	//超过end时间时就退出进程
	// if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec) {
	// 	printf("%s count = %lld\n", str, count);
	// 	exit(0);
	// }
	if((tv.tv_sec*1000000+tv.tv_usec) > (end.tv_sec*1000000+end.tv_usec)) {
		printf("%s count = %lld\n", str, count);
		exit(0);
	}
}