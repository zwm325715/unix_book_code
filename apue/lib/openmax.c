//图2-17 确定文件描述符个数
#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef	OPEN_MAX
static long	openmax = OPEN_MAX;
#else
static long	openmax = 0;
#endif

/*
 * If OPEN_MAX is indeterminate, this might be inadequate.
 */
#define	OPEN_MAX_GUESS	256

// 获取一个进程可以打开的最大fd个数
long open_max(void) {
	if (openmax == 0) {		/* first time through */
		errno = 0;
		if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
			if (errno == 0)
				openmax = OPEN_MAX_GUESS;	/* it's indeterminate */
			else
				err_sys("sysconf error for _SC_OPEN_MAX");
		}
	}
	return(openmax);
}
