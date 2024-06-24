#include "apue.h"
#include <dirent.h>

/*
	1.列出一个目录中所有文件的"名字"
	2.实参:目录名全路径
*/
int main(int argc, char *argv[]) {
	DIR				*dp;
	struct dirent	*dirp;

	if (argc != 2)
		err_quit("usage: ls directory_name");
	//打开"输入的目录"
	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);
	//读取目录dp对象下的所有信息
	while ((dirp = readdir(dp)) != NULL) {
		//只输出"文件/目录"的名字:
		// 使用该名字，此后就可以调用stat函数以获取该文件的所有属性
		printf("%s\n", dirp->d_name);
	}
	//关闭资源
	closedir(dp);
	//0表示正常结束;[1-255]表示出错
	exit(0);
}
