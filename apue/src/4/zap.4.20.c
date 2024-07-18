#include "apue.h"
#include <fcntl.h>
//图4-21:通过futimens重置访问时间和修改时间，但是i-node状态变更时间不能重置(open的时间)
int main(int argc, char *argv[]) {
	int				i, fd;
	struct stat		statbuf;
	struct timespec	times[2];

	for (i = 1; i < argc; i++) {
		/* fetch current times 用stat函数目的是获取文件的目前时间*/
		if (stat(argv[i], &statbuf) < 0) {	
			err_ret("%s: stat error", argv[i]);
			continue;
		}
		/* truncate 把这个文件截断到0;此时会影响到st_ctim的变化*/
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { 
			err_ret("%s: open error", argv[i]);
			continue;
		}
		//访问时间
		times[0] = statbuf.st_atim;
		//修改时间
		times[1] = statbuf.st_mtim;
		/* reset times 重置时间*/
		if (futimens(fd, times) < 0)		
			err_ret("%s: futimens error", argv[i]);
		close(fd);
	}
	exit(0);
}
