#include "apue.h"

//图10-19 通过SA_INTERRUPT选项阻止被中断的系统调用重启动
Sigfunc *  signal_intr(int signo, Sigfunc *func) {
	struct sigaction	act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
#ifdef	SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;
#endif
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}
