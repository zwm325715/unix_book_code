#include	"unp.h"

//图5-14:调用writen两次的函数
void str_cli_5_13(FILE *fp, int sockfd) {
  char	sendline[MAXLINE], recvline[MAXLINE];

  while (Fgets(sendline, MAXLINE, fp) != NULL) {
    //调用write 2次
    Writen(sockfd, sendline, 1);//写入1个字节:目的引发一个RST
    sleep(1);//暂停1s
    Writen(sockfd, sendline+1, strlen(sendline)-1);//写入剩余字节:目的产生SIGPIPE

    if (Readline(sockfd, recvline, MAXLINE) == 0)
      err_quit("str_cli: server terminated prematurely");

    Fputs(recvline, stdout);
  }
}
