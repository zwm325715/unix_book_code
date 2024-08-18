#include "stdio.h"

/*
    两个".symver汇编器指令"将这"两个函数"绑定到了两个不同的"版本标签"上
*/
// 指示与版本标签VER_1进行链接的应用程序(p1)所使用的xyz()的实现是xyz_old()
__asm__(".symver xyz_old,xyz@VER_1");
/*
    1.指示与版本标签VER_2进行链接的应用程序所使用的xyz()的实现是xyz_new()
    2.'@@'(两个'@')是用来:
        指示当"应用程序"与这个共享库进行"静态链接"时应该使用的xyz()的"默认定义"
        同一个符号的.symver指令应该"只有一个"指令使用"@@标记"
*/
__asm__(".symver xyz_new,xyz@@VER_2");

/*
    1.库中2个版本的xyz()
        通过真实函数xyz_old()和xyz_new()来实现
*/
//对应旧的xyz()
void xyz_old(void) {
    printf("v1 xyz\n");
}
/*
    1.对应新的xyz()
    2.与库的新版本进行链接的程序所使用的xyz()的定义
*/
void xyz_new(void) {
    printf("v2 xyz\n");
}
// 新增的其他函数
void pqr(void){
    printf("pqr\n");
}