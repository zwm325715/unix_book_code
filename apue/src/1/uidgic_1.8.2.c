#include "apue.h"

//打印用户ID和组ID
int main(void) {
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}
