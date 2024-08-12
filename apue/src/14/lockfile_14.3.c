#include <unistd.h>
#include <fcntl.h>

//图14-9 在文件整体上加一把写锁
int lockfile(int fd) {
	struct flock fl;
	
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return(fcntl(fd, F_SETLK, &fl));
}
