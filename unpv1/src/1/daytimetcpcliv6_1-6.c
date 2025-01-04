#include	"unp.h"

/**
 * 图1-6:适用于IPv6的图1-5所示程序的修改版
 * @param argc
 * @param argv
 *   1:支持获取时间的服务器IP地址
 * @return
 */
int main(int argc, char **argv) {
  int					sockfd, n;
  struct sockaddr_in6/*变更点*/	servaddr;
  char				recvline[MAXLINE + 1];

  if (argc != 2)
    err_quit("usage: a.out <IPaddress>");

  if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
    err_sys("socket error");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin6_family/*变更点*/ = AF_INET6/*变更点*/;
  servaddr.sin6_port/*变更点*/   = htons(13);	/* daytime server */
  if (inet_pton(AF_INET6/*变更点*/,
                argv[1],
                &servaddr.sin6_addr/*变更点*/) <= 0)
    err_quit("inet_pton error for %s", argv[1]);

  if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    err_sys("connect error");

  while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
    recvline[n] = 0;	/* null terminate */
    if (fputs(recvline, stdout) == EOF)
      err_sys("fputs error");
  }
  if (n < 0)
    err_sys("read error");

  exit(0);
}
