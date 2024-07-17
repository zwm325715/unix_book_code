#include "apue.h"
#include <sys/wait.h>
/**
	实例8-8fork两次以避免僵死进程
		如果一个进程fork了一个子进程，但是该父进程不需要它等待子进程终止，
		也不希望子进程处于僵死状态(一直到父进程终止)，
		实现这一要求的窍门就是调用fork两次
*/
int main(void) {
	pid_t	pid;
	//首次创建子进程
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {/* 子进程执行 first child */
		//再fork一次,创建孙子进程
		if ((pid = fork()) < 0) {//注意:pid不会影响到父进程中的pid
			err_sys("fork error");
		} else if (pid > 0) {//子进程(first)执行
			/* 子进程=孙子进程的父进程 parent from second fork == first child */
			//子进程退出(孙子进程的父进程变为init进程)
			exit(0);
		}
		//让孙子进程(second)继续进行干我们的业务逻辑
		/*
		 * 我们是孙子进程;在上面的语句中，一旦它真正的父进程调用exit()，
		 * 它的父进程就变成了init进程
		 * We're the second child; our parent becomes init as soon
		 * as our real parent calls exit() in the statement above.
		 * 这里是孙子进程继续执行的地方，init知道这个进程完成时，
		 * 就获取孙子进程的状态，从而脱离了僵死状态
		 * Here's where we'd continue executing, knowing that when
		 * we're done, init will reap(/riːp/ 获得;收获；收割) our status.
		 */
		/**
		睡了2s:"保证"在打印父进程ID时第一个子进程(子进程)已终止，让init进程接管孙子进程
		   就是为了避免(这样也不一定哦，只是大概率)出现
		   "孙子进程先退出了，子进程还没有退出，也没wait"的情况，
		   此时孙子就是僵死进程
		*/
		sleep(2);
		//输出孙子进程的父进程
		printf("second child, parent pid = %ld", (long)getppid());
		//孙子进程退出(init进程会进行wait操作，避免了僵死)
		exit(0);
	}
	//等待的是"子进程(first)"终止
	if (waitpid(pid, NULL, 0) != pid) {	/* wait for first child */
		err_sys("waitpid error");
	}
		
	/*我们是父进程(原始进程);我们继续执行，要知道的我们已经不是"孙子进程"的父进程
	 * We're the parent (the original process); we continue executing,
	 * knowing that we're not the parent of the second child.
	 */
	exit(0);
}
