#include "vis_comm_42.3.1.h"
//由vis_f1()和vis_f2()调用,但不想被与该库进行链接的应用程序直接使用
int vis_comm() {
    return 100;
}