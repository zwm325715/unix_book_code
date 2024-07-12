#include "apue.h"
#include <shadow.h>
//习题2
/* Linux/Solaris version */
int main(void) {
	struct spwd	*ptr;
	//访问阴影口令文件(必须是root用户才能执行)
	if ((ptr = getspnam("ob")) == NULL)
		err_sys("getspnam error");
	//输出"加密口令"
	printf("sp_pwdp = %s\n", 
		ptr->sp_pwdp == NULL || 
		ptr->sp_pwdp[0] == 0 ?  "(null)" : ptr->sp_pwdp);
	exit(0);
}
