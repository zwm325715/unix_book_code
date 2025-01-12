/* include signal */
#include	"unp.h"
/**
 * 使用sigaction包装的signal函数:
 *   系统的signal实现是早于POSIX出现的历史悠久的函数，调用时，不同的实现
 *   提供不同的信号语义以达成向后兼容，而POSIX明确规定了调用sigaction时的语义,
 *   因此使用sigaction进行了包装.
 * @param signo 要处理的信号编号
 * @param func
 * @return 旧的信号处理函数
 */
Sigfunc * signal(int signo, Sigfunc *func) {
    //结构变量
	struct sigaction	act, oact/*旧动作*/;

    //信号捕捉函数的地址
	act.sa_handler = func;
    //调用handler之前信号屏蔽字(阻塞)的信号集 进行清空:handler执行期间不阻塞额外的信号
	sigemptyset(&act.sa_mask);
    //信号选项无
	act.sa_flags = 0;

    /*
     * 对 SIGALRM 进行特殊处理的原因在于:
     *     产生该信号的目的正如14.2节讨论的那样,通常是为I/O操作设置超时,
     *     这种情况下我们希望受阻塞的系统调用被该信号中断掉
     */
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x 这是个系统 */
#endif
	} else {//非SIGALRM信号
//如果os中有定义SA_RESTART(centos7有)
#ifdef	SA_RESTART
        //设置SA_RESTART标志:由此信号中断的系统调用自动重启动
		act.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
    //sigaction系统调用
	if (sigaction(signo, &act, &oact) < 0) {
		return(SIG_ERR);
    }
    //返回信号的旧handler
	return (oact.sa_handler);
}
/* end signal */

/* for our signal() function */
Sigfunc * Signal(int signo, Sigfunc *func) {
	Sigfunc	*sigfunc;

	if ( (sigfunc = signal(signo, func)) == SIG_ERR)
		err_sys("signal error");
	return(sigfunc);
}
