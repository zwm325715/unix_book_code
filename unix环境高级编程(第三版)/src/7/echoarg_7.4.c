#include "apue.h"
//图7-4：将所有命令行参数都回显到标准输出
int main(int argc, char *argv[]) {
	int		i;
	/* echo all command-line args */
	for (i = 0; i < argc; i++)
		printf("argv[%d]: %s\n", i, argv[i]);
	//ISO C和POSIX.1都要求argv[argc]是一个空指针，因此循环可改写为
	// for(i=0;argv[i]!=NULL;i++)
	exit(0);
}
