#include "apue.h"

//打印进程ID
int main(void) {
    // long类型
	printf("hello world from process ID %ld\n", (long)getpid());
	exit(0);
}
