#include	"unp.h"
//从fp文件中读，发送给sockfd,然后将socket的返回结果输出到标准输出
void str_cli(FILE *fp, int sockfd) {
	char	sendline[MAXLINE]/*发送缓冲区*/, recvline[MAXLINE];
    //从fp读取一行
	while (Fgets(sendline, MAXLINE, fp) != NULL) {
        //写到sockfd
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
        //输出到stdout
		Fputs(recvline, stdout);
	}
}
