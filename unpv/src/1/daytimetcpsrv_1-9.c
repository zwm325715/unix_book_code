#include	"unp.h"
#include	<time.h>

/**
 * 图1-9 TCP时间获取服务器程序
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  int					listenfd, connfd;
  struct sockaddr_in	servaddr;
  char				buff[MAXLINE];
  time_t				ticks;
  //1.创建TCP套接字
  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  //2.把服务器的中所周知端口捆绑到套接字
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  /*
  INADDR_ANY: 该IP地址表示如下含义
    如果服务器主机有多个网络接口,服务器进程可以在任意网络接口上接收客户连接
    注:以后将了解怎么限定服务器进程只在单个网络接口上接收客户连接.
   */
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(13);	/* daytime server */
  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

  //3.把套接字转换成监听套接字
  //LISTENQ:系统内核允许在这个监听描述符上排队的最大客户全连接数(更多参考4.5节).
  Listen(listenfd, LISTENQ/*backlog:1024*/);

  //4.接收客户连接,发送应答
  for ( ; ; ) {//死循环
    //阻塞等待客户端连接
    connfd/*新的已连接描述符*/ = Accept(listenfd/*监听描述符*/, (SA *) NULL, NULL);
    //库函数返回当前时间和日期:距离格里尼治时间秒数
    ticks = time(NULL);
    //转换格式
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    fputs(buff,stdout);
    //发送给客户端
    Write(connfd, buff, strlen(buff));

    //5.终止连接
    Close(connfd);
  }
}
