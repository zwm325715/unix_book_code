#include	"unp.h"
#include	<time.h>

/**
 * 可以显示客户IP地址和端口号的时间获取服务器程序
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  int	listenfd, connfd;
  //一个 值-结果 变量
  socklen_t			len;
  struct sockaddr_in	servaddr, cliaddr/*IPv4:存放客户端的协议地址*/;
  char				buff[MAXLINE];
  time_t				ticks;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(13);	/* daytime server */

  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);

  for ( ; ; ) {
    //len初始化为套接字地址结构的大小
    len = sizeof(cliaddr);
    //注意第2个参数和第3个参数:用来存放连接的客户端信息
    connfd = Accept(listenfd, (SA *) &cliaddr, &len);
    printf("connection from %s, port %d\n",
           //地址转换为点分
           Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
           //端口转为主机字节序
           ntohs(cliaddr.sin_port));

    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    Write(connfd, buff, strlen(buff));

    Close(connfd);
  }
}
