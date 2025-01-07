#include	"unp.h"
/**
 * 只设置一个套接字地址结构中的端口部分
 * @param sa
 * @param salen
 * @param port
 */
void sock_set_port(struct sockaddr *sa, socklen_t salen, int port) {
	switch (sa->sa_family) {
      case AF_INET: {
          struct sockaddr_in	*sin = (struct sockaddr_in *) sa;
          sin->sin_port = port;
          return;
      }

#ifdef	IPV6
	case AF_INET6: {
		struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;
		sin6->sin6_port = port;
		return;
	}
#endif
	}

    return;
}
