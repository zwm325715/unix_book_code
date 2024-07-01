#include "apue.h"

// 图3-1:测试标准输入能否被设置偏移量
int main(void) {
	if (lseek(STDIN_FILENO/*0*/, 0, SEEK_CUR) == -1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");
	exit(0);
}
