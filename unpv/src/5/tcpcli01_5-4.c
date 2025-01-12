#include	"unp.h"
/**
 * TCP回射客户程序
 * @param argc
 * @param argv 服务器的IP地址
 * @return
 */
int main(int argc, char **argv) {
  int					sockfd;
  struct sockaddr_in	servaddr;

  if (argc != 2) {
    err_quit("usage: tcpcli <IPaddress>");
  }

  sockfd = Socket(AF_INET, SOCK_STREAM, 0);
  //目标地址
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);//9877
  //命令行输入的IP地址转换为二进制形式放到servaddr.sin_addr中
  Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
  //发送数据
  str_cli(stdin, sockfd);	/* do it all */

  exit(0);
}
