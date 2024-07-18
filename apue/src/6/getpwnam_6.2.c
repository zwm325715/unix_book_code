#include <pwd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct passwd * getpwnam(const char *name);

int main() {
    char userName[] = "ob";
    struct passwd * res = getpwnam(userName);
    if(res) {
        printf("找到ob用户了!name=%s,uid=%d,gid=%d,dir=%s,shell=%s\n",
            res->pw_name,
            res->pw_uid,
            res->pw_gid,
            res->pw_dir,
            res->pw_shell
            );
    }else {
        printf("没有找到ob用户！");
    }
    exit(0);
}

//实例5-2程序给出了getpwnam函数的一个实现(用getpwent来实现)
struct passwd * getpwnam(const char *name) {
    struct passwd  *ptr;
    /*
    自我保护:
        确保如果调用者之前已经调用了getpwent打开了有关文件，
        "反绕有关文件"使它们定位到"文件开始"处.
    */
    setpwent();
    /**
    1.循环读取每一个记录项
    2.这里用了小窍门：到达文件尾部或出错时为NULL，当成了返回值返回了
    */
    while ((ptr = getpwent()) != NULL) {
        
        //如果找到一个跟入参name匹配的用户名，就结束循环,返回该ptr
        if (strcmp(name, ptr->pw_name) == 0) {
            break;		/* found a match */
        }
            
    }
    //关闭相关文件
    endpwent();
    //由于是一个静态变量，因此可以返回(没有找到时为null)
    return(ptr);	/* ptr is NULL if no match found */
}
