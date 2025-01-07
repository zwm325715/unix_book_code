/* include sockfd_to_family */
#include	"unp.h"

/**
 * 获取套接字sockfd的地址族
 * @param sockfd
 * @return
 */
int sockfd_to_family(int sockfd) {
    /*
    由于不知道要分配的套接字地址结构类型，所以采用sockaddr_storage通用结构:
      可以承载系统支持的任何套接字地址结构
    */
	struct sockaddr_storage ss;
	socklen_t	len;
    //值-结果  类型的变量，所以需要先赋值再有内核填充
	len = sizeof(ss);
    //取到本地协议地址
	if (getsockname(sockfd, (SA *) &ss, &len) < 0)
		return(-1);
    //返回地址族
	return(ss.ss_family);
}

/* end sockfd_to_family */

int
Sockfd_to_family(int sockfd)
{
	int		rc;

	if ( (rc = sockfd_to_family(sockfd)) < 0)
		err_sys("sockfd_to_family error");

	return(rc);
}
