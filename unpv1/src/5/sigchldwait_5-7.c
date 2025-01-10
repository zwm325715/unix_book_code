#include	"unp.h"
//SIGCHLD信号的handler：处理僵死子进程
void sig_chld(int signo) {
  pid_t	pid;//子进程ID
  int		stat;//子进程终止状态

  pid = wait(&stat);//收尸子进程
  //在信号处理函数中不适合调用printf这样的标准I/O函数:11.18节会讨论
  printf("child %d terminated\n", pid);
  return;
}
