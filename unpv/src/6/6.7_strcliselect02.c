#include	"unp.h"

//改用read和write取消对缓冲区的使用
void str_cli(FILE *fp, int sockfd) {
  int			maxfdp1, stdineof;
  fd_set		rset;
  char		buf[MAXLINE];
  int		n;

  stdineof = 0;//标准输入是否终止(可读性):0表示可读;1表示不可读
  FD_ZERO(&rset);
  for ( ; ; ) {
    //标准输入没有终止时(可读)
    if (stdineof == 0) {
      //每次循环都开启标准输入
      FD_SET(fileno(fp), &rset);
    }
    //每次循环都开启sockfd
    FD_SET(sockfd, &rset);
    maxfdp1 = max(fileno(fp), sockfd) + 1;
    Select(maxfdp1, &rset, NULL, NULL, NULL);

    //sockfd套接字就绪(可读)时
    if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
      //对于服务器发送了一个FIN(正常的终止,服务器不再发数据了),read就返回0(EOF表示文件尾)
      if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
        if (stdineof == 1) {//此时标准输入也终止(不可读)时
          return; /* normal termination 正常返回*/
        } else {//标准输入还没有终止(没有遇到EOF)
          //通知终止：客户端感知到了(kill -9 服务器进程即可观察到)
          err_quit("str_cli: server terminated prematurely");
        }
      }
      //写到标准输出
      Write(fileno(stdout), buf, n);
    }

    //标准输入可读时
    if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
      //标准输入终止时:read读到的是0(EOF),sockfd可以继续读
      if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
        stdineof = 1;//标准输入不可读
        //半关闭(不再写):向服务器发送FIN
        Shutdown(sockfd, SHUT_WR);	/* send FIN */
        FD_CLR(fileno(fp), &rset);//清除掉标准输入的fd位，不再select
        continue;//继续循环
      }
      //发送给服务器
      Writen(sockfd, buf, n);
    }
  }
}
