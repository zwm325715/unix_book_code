/* include writen */
#include	"unp.h"

/* Write "n" bytes to a descriptor. */
ssize_t	writen(int fd, const void *vptr, size_t n) {
	size_t		nleft;//按照入参n要求写入的剩余字节数
	ssize_t		nwritten;//1次write系统调用写入的字节数
	const char	*ptr;//从哪个缓冲区读数据

	ptr = vptr;//初始为入参vptr
	nleft = n;//初始为入参n
	while (nleft > 0) {
        //从ptr读取nleft个字节写入到fd
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            //处理write系统调用被中断的问题
			if (nwritten < 0 && errno == EINTR) {
				nwritten = 0;		/* and call write() again */
            } else {//其他情况就是错误
              return (-1);            /* error */
            }
		}
        //更新剩余要写入的字节数
		nleft -= nwritten;
        //更新缓冲区指针位置
		ptr   += nwritten;
	}
	return(n);
}

/* end writen */

void
Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}
