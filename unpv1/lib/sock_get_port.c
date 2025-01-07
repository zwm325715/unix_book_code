#include	"unp.h"

/**
 * 返回端口号
 * @param sa
 * @param salen
 * @return
 *    若为IPv4或IPv6地址，则为非负端口号
 *    其他为-1
 */
int sock_get_port(const struct sockaddr *sa, socklen_t salen) {
	switch (sa->sa_family) {
      case AF_INET: {
          struct sockaddr_in	*sin = (struct sockaddr_in *) sa;
          return(sin->sin_port);
      }

#ifdef	IPV6
      case AF_INET6: {
          struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;
          return(sin6->sin6_port);
      }
#endif
	}

    return(-1);		/* ??? */
}
