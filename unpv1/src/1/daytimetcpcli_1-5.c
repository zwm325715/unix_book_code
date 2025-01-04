#include "unp.h"

/**
 * 图1-5:TCP时间获取程序  => daytimetcpcli_1-5.c
 *     只支持IPV4
 * @param argc
 * @param argv
 *   1:支持获取时间的服务器IP地址
 * @return
 */
int main(int argc, char **argv) {
  int	sockfd, n;
  //读取缓冲区
  char	recvline[MAXLINE + 1/*null terminate*/];
  //网际套接字地址结构:可以把目标机器的IP地址和端口号填入
  struct sockaddr_in servaddr;

  if (argc != 2)
    err_quit("usage: a.out <IPaddress>");
  //1.创建一个套接字，返回该套接字的描述符
  if ( (sockfd = socket(AF_INET/*网际*/, SOCK_STREAM/*字节流*/, 0)) < 0) {
    err_sys("socket error");
  }

  //2.指定服务器的IP地址和端口
  //清0：被memset替代了
  bzero(&servaddr, sizeof(servaddr));
  //协议族
  servaddr.sin_family = AF_INET;
  /*
   端口号为13：
     servaddr中的IP地址和端口号必须使用特定格式，
     使用htons进行"主机到网络短整数"来将13转换为二进制端口号
  */
  servaddr.sin_port = htons(13);	/* daytime server */
  /*
    a).inet_pton : convert IPv4 and IPv6 addresses from text to binary form
      #include <arpa/inet.h>
      int inet_pton(int af, const char *src, void *dst);

      这是一个支持IPv6的新函数，以前的代码使用inet_addr函数来把ASCII点分十进制数串变换成正确的格式,
      不过inet_addr函数有不少局限，在新函数inet_pton中得以纠正
    b).把IP地址字符串转换为二进制形式放到servaddr中
   */
  if (inet_pton(AF_INET, argv[1]/*IP地址*/, &servaddr.sin_addr) <= 0) {
    err_quit("inet_pton error for %s", argv[1]);
  }

  //3.建立与服务器的TCP连接
  if (connect(sockfd,
              //每当一个套接字函数需要一个指向某个套接字地址结构的指针时
              //这个指针必须强制类型转换成一个指向通用套接字地址结构的指针(历史原因)。
              (SA/* struct sockaddr */ *) &servaddr/*强转*/,
              sizeof(servaddr)) < 0) {
    err_sys("connect error");
  }

  //4.读入并输出服务器的应答
  /*
   a) TCP本身不提供记录结束标志，需要应用自己确定边界
   b) 由于不能确保一次read调用能返回服务器的整个应答，因此需要使用循环.
   c) 返回值:
       0    -  对端关闭连接
       负值  -  发生错误
   */
  while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
    /* null terminate */
    recvline[n] = 0;
    //使用标准IO输出结果
    if (fputs(recvline, stdout) == EOF) {
      err_sys("fputs error");
    }
  }
  if (n < 0) {
    err_sys("read error");
  }

  //5. 终止程序
  //Unix在一个进程终止时总是关闭该进程所有打开的描述符,因此TCP套接字就此被关闭.
  //也就是隐藏执行了close(sockfd);
  exit(0);
}
