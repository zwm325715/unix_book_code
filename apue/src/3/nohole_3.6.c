#include "apue.h"
#include <fcntl.h>

char	buf[] = "a";

//3.6:创建一个没有空洞的文件
int main(void) {
	int	fd;
    int count;

	if ((fd = creat("file.nohole", FILE_MODE)) < 0)
		err_sys("creat nohole error");
    for (count = 0; count < 16394; count++) {
        if (write(fd, buf, 1) != 1)
		    err_sys("buf1 write error");
    }

	exit(0);
}
