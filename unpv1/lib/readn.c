/* include readn */
#include	"unp.h"

/* Read "n" bytes from a descriptor. */
ssize_t	readn(int fd, void *vptr, size_t n) {
	size_t	nleft;//按照入参n要求读取的剩余字节数
	ssize_t	nread;//1次read系统调用读取到的字节数
	char	*ptr;//读到的数据放入的缓冲区

	ptr = vptr;//初始为入参vptr
	nleft = n;//初始为入参n
	while (nleft > 0) {
        //从fd中读取nleft个字节到ptr指针
		if ( (nread = read(fd, ptr, nleft)) < 0) {
            //处理read系统调用被中断的问题
			if (errno == EINTR) {
			  nread = 0;	/* and call read() again */
            } else {//其他情况报错
			  return(-1);
            }
		} else if (nread == 0) {//结束
			break; /* EOF */
        }
        //更新剩余要读取的字节数
		nleft -= nread;
        //更新缓冲区指针位置
		ptr   += nread;
	}
    //返回读取到的字节数
	return(n - nleft);		/* return >= 0 */
}
/* end readn */

ssize_t
Readn(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;

	if ( (n = readn(fd, ptr, nbytes)) < 0)
		err_sys("readn error");
	return(n);
}
