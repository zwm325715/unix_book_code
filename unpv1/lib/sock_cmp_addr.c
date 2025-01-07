#include	"unp.h"

#ifdef	HAVE_SOCKADDR_DL_STRUCT
#include	<net/if_dl.h>
#endif

/**
 * 比较2个套接字地址结构的地址部分
 * @param sa1
 * @param sa2
 * @param salen
 * @return 同一协议族且相同时为0,否则为非0
 */
int sock_cmp_addr(const struct sockaddr *sa1,
                  const struct sockaddr *sa2,
			      socklen_t salen) {
	if (sa1->sa_family != sa2->sa_family)
		return(-1);

	switch (sa1->sa_family) {
      //IPv4
      case AF_INET: {
          //比较地址字节内容是否相等
          return(memcmp( &((struct sockaddr_in *) sa1)->sin_addr,
                         &((struct sockaddr_in *) sa2)->sin_addr,
                         sizeof(struct in_addr)));
      }

#ifdef	IPV6
	case AF_INET6: {
		return(memcmp( &((struct sockaddr_in6 *) sa1)->sin6_addr,
					   &((struct sockaddr_in6 *) sa2)->sin6_addr,
					   sizeof(struct in6_addr)));
	}
#endif

#ifdef	AF_UNIX
	case AF_UNIX: {
		return(strcmp( ((struct sockaddr_un *) sa1)->sun_path,
					   ((struct sockaddr_un *) sa2)->sun_path));
	}
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
	case AF_LINK: {
		return(-1);		/* no idea what to compare here ? */
	}
#endif
	}
    return (-1);
}
