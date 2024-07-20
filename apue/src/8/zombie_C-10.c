#include "apue.h"

#ifdef SOLARIS
#define PSCMD	"ps -a -o pid,ppid,s,tty,comm"
#else
// linux是这个
#define PSCMD	"ps -o pid,ppid,state,tty,command"
#endif
//习题8.6:创建一个僵死进程
int main(void) {
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)	/* child */
		//子进程直接退出
		exit(0);

	/* parent 父进程没有收尸*/
	sleep(4);
	//父进程执行"ps -o pid,ppid,state,tty,command"命令
	//state：Z表示僵死进程
	system(PSCMD);

	exit(0);
}
