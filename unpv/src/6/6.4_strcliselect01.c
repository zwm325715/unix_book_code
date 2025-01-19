#include	"unp.h"

/**
 * 图6-9:使用select的str_cli函数的实现(在图6-13中改进)：
 *   该版本使用select驱动;5.5节是使用fgets来驱动的
 * @param fp 标准IO
 * @param sockfd 套接字
 */
void str_cli_6_4(FILE *fp, int sockfd) {
  int			maxfdp1;
  fd_set		rset;
  char		sendline[MAXLINE], recvline[MAXLINE];

  //将rset的所有位置0
  FD_ZERO(&rset);
  //死循环
  for ( ; ; ) {
    //开启rset中的fp位
    FD_SET(fileno(fp)/*把标准IO文件指针转换为对应的fd*/, &rset);
    //开启rset中的sockfd位
    FD_SET(sockfd, &rset);
    //计算内核select要测试的fd个数参数值：最大fd+1
    maxfdp1 = max(fileno(fp), sockfd) + 1;
    //IO多路复用select调用
    Select(maxfdp1, &rset/*读fd集*/, NULL, NULL, NULL/*永远等待*/);

    //sockfd套接字就绪(可读)时
    if (FD_ISSET(sockfd, &rset)) {
      //读入回射文本行
      if (Readline(sockfd, recvline, MAXLINE) == 0) {
        err_quit("str_cli: server terminated prematurely");
      }
      //写到标准输出
      Fputs(recvline, stdout);
    }

    //fp就绪(可读)时
    if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
      //从fp流读一行放到sendline缓冲区中
      if (Fgets(sendline, MAXLINE, fp) == NULL) {
        return;		/* all done */
      }
      //写到sockfd
      Writen(sockfd, sendline, strlen(sendline));
    }
  }
}
