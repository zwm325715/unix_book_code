#include	"unp.h"

//读取客户端sockfd的数据并原样返还给它
void str_echo(int sockfd) {
	ssize_t		n;
	char		buf[MAXLINE];

again:
    //如果客户端sockfd关闭了连接，那么接收到客户的FIN包后将导致服务器read函数返回0
	while ( (n = read(sockfd, buf, MAXLINE)) > 0) {
		Writen(sockfd, buf, n);
    }

	if (n < 0 && errno == EINTR) {
		goto again;
    } else if (n < 0) {
		err_sys("str_echo: read error");
    }
}
