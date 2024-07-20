#include "apue.h"
#include <sys/times.h>

static void	pr_times(clock_t, struct tms *, struct tms *);
static void	do_cmd(char *);

//图8-31:计时并执行所有命令行参数
int main(int argc, char *argv[]) {
	int		i;
	//关闭标准输出缓冲
	setbuf(stdout, NULL);
	//循环调用
	for (i = 1; i < argc; i++)
		/* once for each command-line arg */
		do_cmd(argv[i]);
	exit(0);
}

/* execute and time the "cmd" */
static void do_cmd(char *cmd) {
	struct tms	tmsstart, tmsend;
	clock_t		start, end;
	int			status;
	//输出命令字符串
	printf("\ncommand: %s\n", cmd);
	/* starting values 起始值*/
	if ((start = times(&tmsstart)) == -1) {//出错
		err_sys("times error");
	}

	/* execute command 执行命令*/
	if ((status = system(cmd)) < 0) {
		err_sys("system() error");
	}

	/* ending values 结束值*/
	if ((end = times(&tmsend)) == -1) {
		err_sys("times error");
	}

	pr_times(end-start/*滴答差值*/, 
			&tmsstart,
			&tmsend);
	pr_exit(status);
}

//统计时间
static void pr_times(clock_t real, /*墙上时钟滴答差值*/
					struct tms *tmsstart, 
					struct tms *tmsend) {
	static long	clktck = 0;

	/* 
		fetch clock ticks per second first time 
		第一次取每秒的时钟滴答数
	*/
	if (clktck == 0) {
		//每秒时钟滴答数
		if ((clktck = sysconf(_SC_CLK_TCK)) < 0) {
			err_sys("sysconf error");
		}	
	}
	//%7.2f 表示双精度浮点数，保留小数点后2位
	//秒数=滴答差值/每秒滴答数
	printf("  real(墙上时钟秒数):  %7.2f\n", real / (double) clktck);
	printf("  user(用户CPU时间):  %7.2f\n",
	  (tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
	printf("  sys(系统CPU时间):   %7.2f\n",
	  (tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
	//终止子进程的时间信息  
	printf("  child user(终止子进程的用户CPU时间):  %7.2f\n",
	  (tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
	printf("  child sys(终止子进程的系统CPU时间):   %7.2f\n",
	  (tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}
