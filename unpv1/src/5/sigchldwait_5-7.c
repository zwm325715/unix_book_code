#include	"unp.h"
//SIGCHLD信号的handler：处理僵死子进程
void sig_chld(int signo) {
  pid_t	pid;//子进程ID
  int		stat;//子进程终止状态

  pid = wait(&stat);//收尸子进程
  //在信号处理函数中不适合调用printf这样的标准I/O函数:11.18节会讨论
  printf("wait finish! Child PID= %d terminated\n", pid);
  /*暂时没懂
   * 编程约定:显示给出return语句，即使是void类型
   *   这么做的好处是，当某个系统调用被我们编写的某个信号处理函数中断时,
   *   我们就可以得知该系统调用具体是被哪个信号处理函数的哪个return语句中断的.
   */
  return;
}
