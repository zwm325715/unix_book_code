#include	"unp.h"
#include	<netinet/tcp.h>		/* for TCP_xxx defines */

//1.声明可能得值，因此用union
//对于getsockopt的每个可能的返回值，在union都有一个成员
union val {
    int	 i_val;//int类型的值
    long l_val;
    struct linger linger_val;
    struct timeval timeval_val;
} val;//同时定义了全局变量val

//2.定义函数原型:输出给定套接字选项的不同类型的值
static char	*sock_str_flag(union val *, int);
static char	*sock_str_int(union val *, int);
static char	*sock_str_linger(union val *, int);
static char	*sock_str_timeval(union val *, int);

//3.定义结构并同时初始化变量:sock_opts数组
struct sock_opts {
    const char * opt_str;//optname的描述字符串
    int		opt_level;//level
    int		opt_name;//optname
    char   *(*opt_val_str)(union val *, int);//使用的输出函数
} sock_opts[] = {
        { "SO_BROADCAST",		SOL_SOCKET,	SO_BROADCAST,	sock_str_flag },
        { "SO_DEBUG",			SOL_SOCKET,	SO_DEBUG,		sock_str_flag },
        { "SO_DONTROUTE",		SOL_SOCKET,	SO_DONTROUTE,	sock_str_flag },
        { "SO_ERROR",			SOL_SOCKET,	SO_ERROR,		sock_str_int },
        { "SO_KEEPALIVE",		SOL_SOCKET,	SO_KEEPALIVE,	sock_str_flag },
        { "SO_LINGER",			SOL_SOCKET,	SO_LINGER,		sock_str_linger },
        { "SO_OOBINLINE",		SOL_SOCKET,	SO_OOBINLINE,	sock_str_flag },
        { "SO_RCVBUF",			SOL_SOCKET,	SO_RCVBUF,		sock_str_int },
        { "SO_SNDBUF",			SOL_SOCKET,	SO_SNDBUF,		sock_str_int },
        { "SO_RCVLOWAT",		SOL_SOCKET,	SO_RCVLOWAT,	sock_str_int },
        { "SO_SNDLOWAT",		SOL_SOCKET,	SO_SNDLOWAT,	sock_str_int },
        { "SO_RCVTIMEO",		SOL_SOCKET,	SO_RCVTIMEO,	sock_str_timeval },
        { "SO_SNDTIMEO",		SOL_SOCKET,	SO_SNDTIMEO,	sock_str_timeval },
        { "SO_REUSEADDR",		SOL_SOCKET,	SO_REUSEADDR,	sock_str_flag },
#ifdef	SO_REUSEPORT
        { "SO_REUSEPORT",		SOL_SOCKET,	SO_REUSEPORT,	sock_str_flag },
#else
        { "SO_REUSEPORT",		0,			0,				NULL },
#endif
        { "SO_TYPE",			SOL_SOCKET,	SO_TYPE,		sock_str_int },
#ifdef SO_USELOOPBACK
        { "SO_USELOOPBACK",		SOL_SOCKET,	SO_USELOOPBACK,	sock_str_flag },
#else
        { "SO_USELOOPBACK",		0,			0,				NULL },
#endif
        { "IP_TOS",				IPPROTO_IP,	IP_TOS,			sock_str_int },
        { "IP_TTL",				IPPROTO_IP,	IP_TTL,			sock_str_int },
#ifdef	IPV6_DONTFRAG
        { "IPV6_DONTFRAG",		IPPROTO_IPV6,IPV6_DONTFRAG,	sock_str_flag },
#else
        { "IPV6_DONTFRAG",		0,			0,				NULL },
#endif
#ifdef	IPV6_UNICAST_HOPS
        { "IPV6_UNICAST_HOPS",	IPPROTO_IPV6,IPV6_UNICAST_HOPS,sock_str_int },
#else
        { "IPV6_UNICAST_HOPS",	0,			0,				NULL },
#endif
#ifdef	IPV6_V6ONLY
        { "IPV6_V6ONLY",		IPPROTO_IPV6,IPV6_V6ONLY,	sock_str_flag },
#else
        { "IPV6_V6ONLY",		0,			0,				NULL },
#endif
        { "TCP_MAXSEG",			IPPROTO_TCP,TCP_MAXSEG,		sock_str_int },
        { "TCP_NODELAY",		IPPROTO_TCP,TCP_NODELAY,	sock_str_flag },
#ifdef	SCTP_AUTOCLOSE
        { "SCTP_AUTOCLOSE",		IPPROTO_SCTP,SCTP_AUTOCLOSE,sock_str_int },
#else
        { "SCTP_AUTOCLOSE",		0,			0,				NULL },
#endif
#ifdef	SCTP_MAXBURST
        { "SCTP_MAXBURST",		IPPROTO_SCTP,SCTP_MAXBURST,	sock_str_int },
#else
        { "SCTP_MAXBURST",		0,			0,				NULL },
#endif
#ifdef	SCTP_MAXSEG
        { "SCTP_MAXSEG",		IPPROTO_SCTP,SCTP_MAXSEG,	sock_str_int },
#else
        { "SCTP_MAXSEG",		0,			0,				NULL },
#endif
#ifdef	SCTP_NODELAY
        { "SCTP_NODELAY",		IPPROTO_SCTP,SCTP_NODELAY,	sock_str_flag },
#else
        { "SCTP_NODELAY",		0,			0,				NULL },
#endif
        { NULL,					0,			0,				NULL } //哨兵
};

//main方法
int main(int argc, char **argv) {
  int					fd;
  socklen_t			len;
  struct sock_opts	*ptr;
  //遍历sock_opts数组
  for (ptr = sock_opts; ptr->opt_str != NULL; ptr++) {
    printf("%s: ", ptr->opt_str);
    if (ptr->opt_val_str == NULL) {//没有输出函数时
      printf("(undefined)\n");
    } else {//存在输出函数
      switch(ptr->opt_level) {//根据level判断
        case SOL_SOCKET://套接字层
        case IPPROTO_IP://IPv4层套接字
        case IPPROTO_TCP://TCP层
          //创建IPv4的TCP套接字：用于测试选项
          fd = Socket(AF_INET, SOCK_STREAM, 0);
          break;
#ifdef	IPV6
        case IPPROTO_IPV6:
          //创建IPv6的TCP套接字：用于测试选项
          fd = Socket(AF_INET6, SOCK_STREAM, 0);
          break;
#endif
#ifdef	IPPROTO_SCTP
        case IPPROTO_SCTP:
          //测试SCTP层套接字用的是一个IPv4的SCTP套接字
          fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
          break;
#endif
        default:
          err_quit("Can't create fd for level %d\n", ptr->opt_level);
      }

      len = sizeof(val);//选项值共用体大小
      if (getsockopt(fd,//套接字socket
                     ptr->opt_level,//level
                     ptr->opt_name,//optname
                     &val,//选项值共用体
                     &len) == -1) {
        err_ret("getsockopt error");
      } else {
        //(*fp)()这种方式可以让人一眼知道是个函数指针
        printf("default = %s\n", (*ptr->opt_val_str)(&val/*值*/, len/*长度*/));
        //这种方式也可以：但是此时不知道是个函数指针
        //printf("default = %s\n", ptr->opt_val_str(&val, len));
      }
      close(fd);//关闭套接字
    }
  }
  exit(0);
}

static char	strres[128];//输出的字符串

//标志选项:0->off ; 1->on
static char	* sock_str_flag(union val *ptr, int len) {
  if (len != sizeof(int))
    snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
  else
    snprintf(strres, sizeof(strres),
             "%s", (ptr->i_val == 0) ? "off" : "on");
  return(strres);
}

//int类型
static char	* sock_str_int(union val *ptr, int len) {
  if (len != sizeof(int))
    snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
  else
    snprintf(strres, sizeof(strres), "%d", ptr->i_val);
  return(strres);
}

//linger类型
static char	* sock_str_linger(union val *ptr, int len) {
  struct linger	*lptr = &ptr->linger_val;

  if (len != sizeof(struct linger))
    snprintf(strres, sizeof(strres),
             "size (%d) not sizeof(struct linger)", len);
  else
    snprintf(strres, sizeof(strres), "l_onoff = %d, l_linger = %d",
             lptr->l_onoff, lptr->l_linger);
  return(strres);
}

//timeval类型
static char	* sock_str_timeval(union val *ptr, int len) {
  struct timeval *tvptr = &ptr->timeval_val;

  if (len != sizeof(struct timeval))
    snprintf(strres, sizeof(strres),
             "size (%d) not sizeof(struct timeval)", len);
  else
    snprintf(strres, sizeof(strres), "%d sec, %d usec",
             tvptr->tv_sec, tvptr->tv_usec);
  return(strres);
}
