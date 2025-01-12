#include	"unp.h"

/**
 * 把一个套接字地址结构中的地址部分置为通配地址
 * @param sa
 * @param salen
 */
void sock_set_wild(struct sockaddr *sa, socklen_t salen) {
	const void	*wildptr;

	switch (sa->sa_family) {
      case AF_INET: {
          //IPv4的通配地址
          static struct in_addr	in4addr_any;
          in4addr_any.s_addr = htonl(INADDR_ANY);
          wildptr = &in4addr_any;
          break;
      }

#ifdef	IPV6
      case AF_INET6: {
          //IPv6的通配地址
          wildptr = &in6addr_any;
          break;
      }
#endif

      default:
          return;
	}
	sock_set_addr(sa, salen, wildptr);
    return;
}
