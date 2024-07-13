#include "apue.h"
#include <setjmp.h>

#define	TOK_ADD	   5

void	do_line(char *);
void	cmd_add(void);
int		get_token(void);

/*
	1.jmp_buf是一个特殊的类型:
		是某种形式的数组，存放在调用longjmp时能用来恢复栈状态的所有信息
	2.由于在longjmp中会引用env变量，所以通常将env变量定义为"全局变量"
*/
jmp_buf	jmpbuffer;
// 图7-11给出了使用setjmp和longjmp后的代码
int main(void) {
	char	line[MAXLINE];
	//希望返回的位置通过setjmp设定
	//直接调用时, 返回0.代码继续往下走
	if (setjmp(jmpbuffer) != 0)
		printf("error");
	
	while (fgets(line, MAXLINE, stdin) != NULL)
		do_line(line);
	exit(0);
}

char	*tok_ptr;
void do_line(char *ptr) {
	int		cmd;
	tok_ptr = ptr;
	while ((cmd = get_token()) > 0) {
		switch (cmd) {
			case TOK_ADD:
				cmd_add();
				break;
		}
	}
}

void cmd_add(void) {
	int		token;

	token = get_token();
	if (token < 0)
		/*
			1.检查到错误时，通过longjmp返回到setjmp
			2.第2个参数时非0的值，它将成为setjmp处返回的值(也就是1)
		*/
		longjmp(jmpbuffer, 1);
}

int get_token(void) {
	longjmp(jmpbuffer, 2);
}