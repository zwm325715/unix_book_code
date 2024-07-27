#include	<signal.h>
#include	<errno.h>

/*
 * <signal.h> usually defines NSIG to include signal number 0.
 * 1.NSIG：信号个数，通常包含信号0(特殊信号)
 * 2.主要用来判断signo非法
 */
#define	SIGBAD(signo)	((signo) <= 0 || (signo) >= NSIG)

//增加信号(*set |= 1)
int sigaddset(sigset_t *set, int signo) {
	//signo非法时
	if (SIGBAD(signo)) {
		errno = EINVAL;
		return(-1);
	}
	/* turn bit on 打开该信号对应的位(置1)*/
	/**
	  1.由于0没用，所以每个信号编号-1后变成从第1位开始使用,
	  	不进行减1操作就会浪费了最低的那一位了
	  2. 1<<0 = 0b0001 = 1;  1<<1 = 0b0010 = 2
	*/
	*set |= 1 << (signo - 1);//对应位置1(或操作)
	return(0);
}
//删除信号(*set &= 0)
int sigdelset(sigset_t *set, int signo) {
	if (SIGBAD(signo)) {//signo非法时
		errno = EINVAL;
		return(-1);
	}
	/* turn bit off 关闭信号位*/
	//通过与运算使该位置0，其他位保持不变
	*set &= ~(1 << (signo - 1));	
	return(0);
}
//测试指定位(*set & 1 != 0即为开启)
int sigismember(const sigset_t *set, int signo) {
	if (SIGBAD(signo)) {//signo非法时
		errno = EINVAL;
		return(-1);
	}
	//0&1=0;1&1=1;
	//该位跟1做与运算后非0就是开启
	return((*set & (1 << (signo - 1))) != 0);
}
