#include "apue.h"
#include <stdio.h>
// 图8-17:供exec调用该程序:回显所有命令行参数和所有环境变量
int main(int argc, char *argv[]) {
	int			i;
	char		**ptr;
	//声明使用全局环境变量
	extern char	**environ;
	printf("************args************\n");
	/* echo all command-line args 打印所有的命令行参数*/	
	for (i = 0; i < argc; i++)		
		printf("argv[%d]: %s\n", i, argv[i]);
	printf("************env************\n");
	/* and all env strings 所有的环境变量 */
	for (ptr = environ; *ptr != 0; ptr++) {
		//忽略LS_COLORS开头的环境变量，原因是太长了，影响视线
		if(strncmp("LS_COLORS", *ptr,9)) {
			printf("%s\n", *ptr);
		}
	}	

	exit(0);
}
