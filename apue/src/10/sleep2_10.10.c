#include	<setjmp.h>
#include	<signal.h>
#include	<unistd.h>

static jmp_buf	env_alrm;
//SIGALRM信号的handler
static void sig_alrm(int signo) {
	//回到标记点，值为1
	longjmp(env_alrm, 1);
}
/**图10-8:sleep的另一个不完善的实现(使用setjmp和longjmp:见7.10节)，
	避免前一个实例的第3个时间间隔带来的竞争问题(没有处理第1个和第2个问题)
*/
unsigned int sleep2(unsigned int seconds) {
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return(seconds);
	// 标记点:希望返回的位置(直接调用时，返回0;longjmp回来后非0)
	if (setjmp(env_alrm) == 0) {
		/* start the timer 启动定时器*/
		alarm(seconds);
		/* next caught signal wakes us up 下一次捕获的信号唤醒我们 */
		pause();
	}
	return(alarm(0));		/* turn off timer, return unslept time */
}
