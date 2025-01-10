#include	"unp.h"
//正确收尸子进程的最终正确版本
void sig_chld(int signo) {
  pid_t	pid;
  int	stat;
  //网络编程注意点3:通过循环调用waitpid来拿到所有的子进程终止状态(避免僵死进程)
  while ( (pid = waitpid(-1,/*任一子进程*/
                         &stat,/*状态*/
                         WNOHANG/*子进程没有终止时非阻塞*/)) > 0)
    //其实最好有个计数器更好：可参考apue
    printf("child %d terminated\n", pid);
  return;
}
