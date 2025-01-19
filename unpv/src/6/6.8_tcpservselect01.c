#include	"unp.h"
//使用单进程和select的TCP服务器程序
int main(int argc, char **argv) {
  int					i, maxi, maxfd, listenfd, connfd, sockfd;
  int					nready, client[FD_SETSIZE];
  ssize_t				n;
  fd_set				rset, allset;
  char				buf[MAXLINE];
  socklen_t			clilen;
  struct sockaddr_in	cliaddr, servaddr;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(SERV_PORT);
  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
  Listen(listenfd, LISTENQ);

  //maxfd+1后是select函数的第一个参数，初始为监听套接字的fd
  maxfd = listenfd;//initialize
  //客户端数组client[]当前使用项的最大下标，初始为-1
  maxi = -1; //index into client[] array
  //client[]数组初始为-1
  for (i = 0; i < FD_SETSIZE/*支持的最大客户端数目*/; i++) {
    client[i] = -1;	/* -1 indicates available entry -1表示可用 */
  }
  //所有的fd集位清0
  FD_ZERO(&allset);
  //先设置监听套接字
  FD_SET(listenfd, &allset);

  for ( ; ; ) {
    //因为要修改fd_set，所以这里拷贝了一份
    rset = allset;	/* structure assignment 结构赋值*/
    //select调用:只关心读事件
    nready = Select(maxfd+1, &rset, NULL, NULL, NULL/*阻塞*/);
    //监听套接字可读时：表示来客户端连接了，保存起来以便进行后续遍历读取
    if (FD_ISSET(listenfd, &rset)) {/* new client connection */
      clilen = sizeof(cliaddr);
      //接收连接
      connfd = Accept(listenfd, (SA * ) & cliaddr, &clilen);
#ifdef    NOTDEF
      printf("new client: %s, port %d\n",
                    Inet_ntop(AF_INET, &cliaddr.sin_addr, 4, NULL),
                    ntohs(cliaddr.sin_port));
#endif
      //保存客户端连接fd:遍历client数组找到可用项
      for (i = 0; i < FD_SETSIZE; i++){
        //可用项
        if (client[i] < 0) {
          //保存下来客户端连接的fd
          client[i] = connfd;    /* save descriptor */
          break;
        }
      }
      //不能超过FD_SETSIZE个
      if (i == FD_SETSIZE) {
        err_quit("too many clients");
      }
      //把这个新的客户端连接fd放到allset中
      FD_SET(connfd, &allset);	/* add new descriptor to set */
      //如有必要:最大fd值变更
      if (connfd > maxfd) {
        maxfd = connfd;	/* for select */
      }
      //如有必要：client数组的最大下标更新
      if (i > maxi) {
        maxi = i;	/* max index in client[] array */
      }

      //nready自减1后 判断监听套接字是否还有可读的(客户端连接)
      if (--nready <= 0) {
        //没有时，去select阻塞
        continue;	/* no more readable descriptors */
      }
    }

    //对于每个现有的客户连接进行遍历检查
    for (i = 0; i <= maxi; i++) {	/* check all clients for data */
      //忽略-1的项
      if ( (sockfd = client[i]) < 0) {
        continue;
      }
      //在rset中时:说明该connfd可读
      if (FD_ISSET(sockfd, &rset)) {
        //读数据(可能阻塞):这里有个另外的问题就是denial of service攻击
        if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
          //0表示客户端关闭连接了：更新对应的数据结构
          /*connection closed by client */
          Close(sockfd);//关闭TCP
          FD_CLR(sockfd, &allset);//从all中清除掉
          client[i] = -1;//不再占用该位置
        } else {
          //回射数据给到客户端
          Writen(sockfd, buf, n);
        }
        //读一次就要减少1次
        if (--nready <= 0)
          break;				/* no more readable descriptors */
      }
    }
  }
}
