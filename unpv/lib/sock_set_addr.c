#include	"unp.h"

/**
 * 把一个套接字地址结构中的"地址部分" 置为 addr指针所指的值
 * @param sa
 * @param salen
 * @param addr
 */
void sock_set_addr(struct sockaddr *sa, socklen_t salen, const void *addr) {
	switch (sa->sa_family) {
      case AF_INET: {
          struct sockaddr_in	*sin = (struct sockaddr_in *) sa;
          //通过memcpy实现
          memcpy(&sin->sin_addr, addr, sizeof(struct in_addr));
          return;
      }

#ifdef	IPV6
	case AF_INET6: {
		struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;
		memcpy(&sin6->sin6_addr, addr, sizeof(struct in6_addr));
		return;
	}
#endif
	}
    return;
}
