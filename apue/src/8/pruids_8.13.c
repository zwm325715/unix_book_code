#include "apue.h"
//图8-25 打印RUID和EUID
int main(void) {
	printf("real uid = %d, effective uid = %d\n", 
			getuid(), geteuid());
	exit(0);
}
