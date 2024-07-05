#include "apue.h"

// 图4-3:取命令行参数，然后打印每一个参数的文件类型
int main(int argc, char *argv[]) {
	int			i;
	struct stat	buf;
	char		*ptr;

	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		//如果是符号链接信息，就取符号链接文件信息，否则就跟stat功能类似
		if (lstat(argv[i], &buf) < 0) {
			err_ret("lstat error");
			continue;
		}
		//普通文件
		if (S_ISREG(buf.st_mode))
			ptr = "regular";
		//目录	
		else if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		//字符特殊文件
		else if (S_ISCHR(buf.st_mode))
			ptr = "character special";
		//块特殊文件
		else if (S_ISBLK(buf.st_mode))
			ptr = "block special";
		//命名管道
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		//符号链接
		else if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		//套接字			
		else if (S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		printf("%s\n", ptr);
	}
	exit(0);
}
