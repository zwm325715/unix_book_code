/* dynload.c
   Usage: dynload library-path function-name
   Demonstrate dynamic loading of libraries. The program loads the
   named library and then executes the named function in that library.
*/
#include <dlfcn.h>
#include "tlpi_hdr.h"

/* 
    Listing 42-1  演示了dlopen API的使用
    参数:
        1.库名字
        2.函数名字
*/
int main(int argc, char *argv[]) {
    /* Handle for shared library 共享库的句柄*/
    void *libHandle;
    /* Pointer to function with no arguments 没有参数的函数指针*/
    void (*funcp)(void);
    const char *err;
    //校验参数
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s lib-path func-name\n", argv[0]);

    /* 
        Load the shared library and get a handle for later use 
        加载共享库并获取一个句柄供后续使用
    */
    libHandle = dlopen(argv[1], RTLD_LAZY/*懒解析*/);
    if (libHandle == NULL) {//加载失败
        fatal("dlopen: %s", dlerror()/*错误字符串*/);
    }

    /* Search library for symbol named in argv[2] 搜索符号名*/
    (void) dlerror(); /* Clear dlerror() 清理错误字符串 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
    //搜索符号
    funcp = (void (*)(void)) dlsym(libHandle, argv[2]);
#pragma GCC diagnostic pop
    //判断是否搜索失败
    err = dlerror();
    if (err != NULL)
        fatal("dlsym: %s", err);
    //调用该函数
    (*funcp)();
    /* Close the library 关闭共享库(减少引用计数)*/
    dlclose(libHandle);    
    //进程退出
    exit(EXIT_SUCCESS);
}
