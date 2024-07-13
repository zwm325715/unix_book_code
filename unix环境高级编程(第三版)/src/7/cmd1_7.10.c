#include "apue.h"

#define	TOK_ADD	   5

void	do_line(char *);
void	cmd_add(void);
int		get_token(void);

//图7-9:程序骨架(读命令，确定命令的类型，处理每一条命令)
int main(void) {
	char	line[MAXLINE];
	//从标准输入读一行
	while (fgets(line, MAXLINE, stdin) != NULL)
		//处理该输入行
		do_line(line);
	exit(0);
}

/* global pointer for get_token() */
char	*tok_ptr;		

/* process one line of input 处理输入行*/
void do_line(char *ptr) {
	int		cmd;

	tok_ptr = ptr;
	//从该输入行中取下一个标记:假定是一条某种形式的命令
	while ((cmd = get_token()) > 0) {
		/* one case for each command */
		//命令选择
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
	/* rest of processing for this command */
}

int get_token(void) {
	/* fetch next token from line pointed to by tok_ptr */
}
