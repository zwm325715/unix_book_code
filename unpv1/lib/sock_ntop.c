#include	"unp.h"

#ifdef	HAVE_SOCKADDR_DL_STRUCT
#include	<net/if_dl.h>
#endif

/* include sock_ntop */
char * sock_ntop(const struct sockaddr *sa/*通用socket地址*/, socklen_t salen/*套接字地址结构长度*/) {
    char	portstr[8];
    //注意:是个静态全局字符串
    static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) {
      //IPv4
      case AF_INET: {
          //强转为IPv4的地址结构指针
          struct sockaddr_in *sin = (struct sockaddr_in *) sa;
          //IPv4地址:二进制 => 点分十进制
          if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) {
              return(NULL);
          }
          //端口:网络字节序 => 主机字节序(2B)
          if (ntohs(sin->sin_port) != 0) {
              snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
              strcat(str, portstr);
          }
          return(str);
      }
/* end sock_ntop */
//支持IPv6时
#ifdef	IPV6
      case AF_INET6: {
          //强转为IPv6的地址结构指针
          struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;
          //格式为:[IPv6十六进制数格式]:十进制端口号
          str[0] = '[';
          //IPv6地址:二进制 => 字符串
          if (inet_ntop(AF_INET6, &sin6->sin6_addr, str + 1, sizeof(str) - 1) == NULL) {
              return(NULL);
          }
          //端口:网络字节序 => 主机字节序(2B)
          if (ntohs(sin6->sin6_port) != 0) {
              snprintf(portstr, sizeof(portstr), "]:%d", ntohs(sin6->sin6_port));
              strcat(str, portstr);
              return(str);
          }
          return (str + 1);
      }
#endif

#ifdef	AF_UNIX
	case AF_UNIX: {
		struct sockaddr_un	*unp = (struct sockaddr_un *) sa;

			/* OK to have no pathname bound to the socket: happens on
			   every connect() unless client calls bind() first. */
		if (unp->sun_path[0] == 0)
			strcpy(str, "(no pathname bound)");
		else
			snprintf(str, sizeof(str), "%s", unp->sun_path);
		return(str);
	}
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
	case AF_LINK: {
		struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;

		if (sdl->sdl_nlen > 0)
			snprintf(str, sizeof(str), "%*s (index %d)",
					 sdl->sdl_nlen, &sdl->sdl_data[0], sdl->sdl_index);
		else
			snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
		return(str);
	}
#endif
	default:
		snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d",
				 sa->sa_family, salen);
		return(str);
	}
    return (NULL);
}

char *
Sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
	char	*ptr;

	if ( (ptr = sock_ntop(sa, salen)) == NULL)
		err_sys("sock_ntop error");	/* inet_ntop() sets errno */
	return(ptr);
}
