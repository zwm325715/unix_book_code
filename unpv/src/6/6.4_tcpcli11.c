/* Use standard echo server; baseline measurements for nonblocking version */
#include	"unp.h"
void str_cli_6_4(FILE *fp, int sockfd);

int main(int argc, char **argv) {
  int					sockfd;
  struct sockaddr_in	servaddr;

  if (argc != 2)
    err_quit("usage: tcpcli <IPaddress>");

  sockfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(9877);
  Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
  //select调用
  str_cli_6_4(stdin, sockfd);		/* do it all */

  exit(0);
}
