#include	<signal.h>
#include	<unistd.h>
// SIGALRM信号的handler
static void sig_alrm(int signo) {
	/* nothing to do, just return to wake up the pause */
}
/*
  图10-7：使用alarm和pause来实现sleep，这是一个简化而不完整的实现：
	进程可使自己休眠一段指定的时间(下面的代码有问题)
*/
unsigned int sleep1(unsigned int seconds) {
	//捕捉SIGALRM信号，设置handler(默认动作是终止进程，所以设置了空的handler)
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return(seconds);
	/* start the timer 开始定时器，seconds秒后产生SIGALRM信号*/
	alarm(seconds);	
	/* next caught signal wakes us up 下一次捕获的信号唤醒我们 */
	pause();//进程挂起直至捕捉到一个信号
	/* turn off timer, return unslept time 关闭定时器*/
	return (alarm(0));	
}
