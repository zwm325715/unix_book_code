#include	"unp.h"
//在OPEN_MAX已经取消，已经变成了资源限制RLIMIT_NOFILE的一部分
//#include	<limits.h>		/* for OPEN_MAX */
#include <sys/resource.h>

int main(int argc, char **argv) {
  struct rlimit resourceLimit;
  int					i, maxi, listenfd, connfd, sockfd;
  int					nready;
  ssize_t				n;
  char				buf[MAXLINE];
  socklen_t			clilen;
  struct sockaddr_in	cliaddr, servaddr;

  if(getrlimit(RLIMIT_NOFILE,&resourceLimit) == -1) {
    err_sys("获取进程资源限制-可打开的fd数失败");
  }
  int open_max = resourceLimit.rlim_cur;
  struct pollfd	client[open_max];//客户端数组供poll使用

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(SERV_PORT);
  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
  Listen(listenfd, LISTENQ);

  //监听套接字占据0号
  client[0].fd = listenfd;
  client[0].events = POLLRDNORM;//普通数据-读
  //初始client数组
  for (i = 1; i < open_max; i++) {
    client[i].fd = -1;		/* -1 indicates available entry */
  };
  //初始化最大索引
  maxi = 0;	/* max index into client[] array */

  for ( ; ; ) {
    nready = Poll(client, maxi+1, INFTIM);//发起poll
    //监听套接字
    if (client[0].revents & POLLRDNORM) {/* new client connection */
      clilen = sizeof(cliaddr);
      //接收客户端连接
      connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
#ifdef	NOTDEF
      printf("new client: %s\n", Sock_ntop((SA *) &cliaddr, clilen));
#endif
      //找一个client数组中未使用的位置保存起来这个客户端连接fd
      for (i = 1; i < open_max; i++) {
        if (client[i].fd < 0) {
          client[i].fd = connfd;	/* save descriptor */
          break;
        }
      }
      //校验
      if (i == open_max) {
        err_quit("too many clients");
      }
      //设置客户端新连接感兴趣的事件：读
      client[i].events = POLLRDNORM;
      //更新client数组当前正在使用的最大索引
      if (i > maxi) {
        maxi = i;				/* max index in client[] array */
      }
      //没有fd就绪时
      if (--nready <= 0)
        continue;				/* no more readable descriptors */
    }
    //检查所有的客户端连接数据：注意从下标1开始
    for (i = 1; i <= maxi; i++) {	/* check all clients for data */
      //跳过无效项
      if ( (sockfd = client[i].fd) < 0) {
        continue;
      }
      //可读或出错时
      if (client[i].revents & (POLLRDNORM | POLLERR)) {
        //读socket
        if ( (n = read(sockfd, buf, MAXLINE)) < 0) {//出错时
          //RST
          if (errno == ECONNRESET) {
            /*4connection reset by client */
#ifdef	NOTDEF
            printf("client[%d] aborted connection\n", i);
#endif
            Close(sockfd);//关闭socket
            client[i].fd = -1;
          } else {
            err_sys("read error");//其他退出(再议)
          }
        } else if (n == 0) {//已到文件尾
          /*4connection closed by client */
#ifdef	NOTDEF
          printf("client[%d] closed connection\n", i);
#endif
          Close(sockfd);//关闭socket:短连接
          client[i].fd = -1;
        } else {//回射
          Writen(sockfd, buf, n);
        }
        //已就绪个数检查:方便退出循环
        if (--nready <= 0)
          break;				/* no more readable descriptors */
      }
    }
  }
}
