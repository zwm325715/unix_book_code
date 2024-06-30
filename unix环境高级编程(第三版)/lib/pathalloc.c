//图2-16 为路径名动态地分配空间
#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef	PATH_MAX
static long	pathmax = PATH_MAX;
#else
static long	pathmax = 0;
#endif

static long	posix_version = 0;//posix版本
static long	xsi_version = 0;

/* If PATH_MAX is indeterminate, no guarantee this is adequate */
#define	PATH_MAX_GUESS	1024

/* also return allocated size, if nonnull */
//为路径名动态分配存储区
char * path_alloc(size_t *sizep) {
	char	*ptr;
	size_t	size;
	//设置posix版本
	if (posix_version == 0)
		posix_version = sysconf(_SC_VERSION);

	if (xsi_version == 0)
		xsi_version = sysconf(_SC_XOPEN_VERSION);

	/* first time through */
	if (pathmax == 0) {		
		errno = 0;
		//_PC_PATH_MAX:注意是相对路径的最大长度
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
			if (errno == 0)//猜测个值
				pathmax = PATH_MAX_GUESS;	/* it's indeterminate */
			else
				err_sys("pathconf error for _PC_PATH_MAX");
		} else {
			/* add one since it's relative to root */
			//+1是因为它相对于'/'(长度为1)
			pathmax++;		
		}
	}

	/*
	 * Before POSIX.1-2001, we aren't guaranteed that PATH_MAX includes
	 * the terminating null byte.  Same goes for XPG3.
	 * 在POSIX.1-2001之前，我们不能保证PATH_MAX包含终止null字节。XPG3也是如此。
	 */
	if ((posix_version < 200112L) && (xsi_version < 4)) //POSIX.1-2001之前
		size = pathmax + 1;
	else
		size = pathmax;
	//malloc分配内存size
	if ((ptr = malloc(size)) == NULL)
		err_sys("malloc error for pathname");

	if (sizep != NULL)
		*sizep = size;//size赋值给入参sizep
	return(ptr);
}
