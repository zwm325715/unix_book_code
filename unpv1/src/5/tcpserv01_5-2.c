#include	"unp.h"

//TCP回射服务器程序
int main(int argc, char **argv) {
  int		listenfd, connfd;
  pid_t		childpid;
  socklen_t	clilen;
  struct sockaddr_in cliaddr, servaddr;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  /*
   通配地址(0):
    如果系统是多宿主机,我们将接受目的地址为任何本地接口的连接
   */
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  //9877:比5000大，比49152小(避免跟临时端口范围冲突)
  servaddr.sin_port        = htons(SERV_PORT);
  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
  //转换成监听套接字
  Listen(listenfd, LISTENQ);

  for ( ; ; ) {
    clilen = sizeof(cliaddr);
    //阻塞在此
    connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
    //为每个客户端派生一个子进程处理
    if ( (childpid = Fork()) == 0) {/* child process */
      //子进程关闭监听套接字
      Close(listenfd);	/* close listening socket */
      str_echo(connfd);	/* process the request */
      exit(0);
    }
    //父进程关闭已连接套接字
    Close(connfd);	/* parent closes connected socket */
  }
}
