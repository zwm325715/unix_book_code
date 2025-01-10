#include	"unp.h"
void sig_chld(int);

int main(int argc, char **argv) {
  int					listenfd, connfd;
  pid_t				childpid;
  socklen_t			clilen;
  struct sockaddr_in	cliaddr, servaddr;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(SERV_PORT);

  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);
  //捕获信号
  Signal(SIGCHLD, sig_chld);	/* must call waitpid() */

  for ( ; ; ) {
    clilen = sizeof(cliaddr);

    if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
      //网络编程注意点2:由于本程序捕获了信号，所以要处理被中断的系统调用
      if (errno == EINTR)
        continue;		/* back to for() */
      else
        err_sys("accept error");
    }
    //网络编程注意点1:当fork子进程时,必须捕获SIGCHLD信号
    if ( (childpid = Fork()) == 0) {	/* child process */
      Close(listenfd);	/* close listening socket */
      str_echo(connfd);	/* process the request */
      exit(0);
    }
    Close(connfd);			/* parent closes connected socket */
  }
}
