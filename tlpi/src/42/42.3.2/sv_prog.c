// 创建一个程序p1来使用这个libsv.so库
#include "stdlib.h"

void xyz(void);
int main(int argc,char * argv[]) {
    xyz();
    exit(EXIT_SUCCESS);
}