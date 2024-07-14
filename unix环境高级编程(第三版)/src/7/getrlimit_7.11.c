#include "apue.h"
#include <sys/resource.h>
// 宏定义:'#'是ISO C的字符串创建算符(也就是构造一个字符串)
#define	doit(name)	pr_limits(#name, name)

static void	pr_limits(char *, int);
//图7-16:打印由系统支持的所有资源当前的软限制和硬限制
int main(void) {
#ifdef	RLIMIT_AS
	doit(RLIMIT_AS);
#endif

	doit(RLIMIT_CORE);
	doit(RLIMIT_CPU);
	doit(RLIMIT_DATA);
	doit(RLIMIT_FSIZE);

#ifdef	RLIMIT_MEMLOCK
	doit(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
	doit(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
	doit(RLIMIT_NICE);
#endif

	doit(RLIMIT_NOFILE);

#ifdef	RLIMIT_NPROC
	doit(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
	doit(RLIMIT_NPTS);
#endif

#ifdef	RLIMIT_RSS
	doit(RLIMIT_RSS);
#endif

#ifdef	RLIMIT_SBSIZE
	doit(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
	doit(RLIMIT_SIGPENDING);
#endif

	doit(RLIMIT_STACK);

#ifdef RLIMIT_SWAP
	doit(RLIMIT_SWAP);
#endif

#ifdef	RLIMIT_VMEM
	doit(RLIMIT_VMEM);
#endif

	exit(0);
}
//打印限制值
static void pr_limits(char *name, int resource) {
	struct rlimit		limit;
	unsigned long long	lim;
	//取resource的限制值放到limit中
	if (getrlimit(resource, &limit) < 0)
		err_sys("getrlimit error for %s", name);
	//输出入参name,格式:左对齐(-)最小20个宽度(20)的字符串
	printf("%-20s  ", name);
	//"软限制"无穷大时(不限制)
	if (limit.rlim_cur == RLIM_INFINITY) {
		printf("%-15s  ","(infinite)");
	} else {//有限制值
		lim = limit.rlim_cur;
		//输出软限制值,格式:左对齐(-)最小15个宽度(15)按长整数类型的十进制(lld)输出
		printf("%-15lld  ", lim);
	}
	//"硬限制"无穷大时(不限制)
	if (limit.rlim_max == RLIM_INFINITY) {
		printf("%-15s  ","(infinite)");
	} else {//有限制值
		lim = limit.rlim_max;
		//输出硬限制值,格式:左对齐(-)最小15个宽度(15)按长整数类型的十进制(lld)输出
		printf("%-15lld", lim);
	}
	//向标准输出输出换行符
	putchar((int)'\n');
}
