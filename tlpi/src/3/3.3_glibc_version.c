#include "stdio.h"
#include <gnu/libc-version.h>

//1.编译期确定glibc版本号(从2.0版本才开始提供)
#ifdef __GLIBC__
//glibc主版本号
#define GLIBC_MAIN_VERSION  __GLIBC__
#else
#define GLIBC_MAIN_VERSION  0
#endif //__GLIBC__

#ifdef __GLIBC_MINOR__
//glibc次版本号
#define GLIBC_MINOR_VERSION  __GLIBC_MINOR__
#else
#define GLIBC_MINOR_VERSION  0
#endif //__GLIBC_MINOR__

int main(int argc, char *argv[]) {
  //glibc compile_time version:2.28
  printf("glibc compile_time version:%d.%d\n",
            GLIBC_MAIN_VERSION,
            GLIBC_MINOR_VERSION);
  
  //2:运行时的glibc版本
  const char * version = gnu_get_libc_version();
  //glibc run_time version:2.28
  printf("glibc run_time version:%s\n",version);
}