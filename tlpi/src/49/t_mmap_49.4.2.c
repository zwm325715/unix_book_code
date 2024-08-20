/* t_mmap.c
   Demonstrate the use of mmap() to create a shared file mapping.
*/
#include <sys/mman.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
//映射长度为10个字节
#define MEM_SIZE 10
/* 
    Listing 49-2 
    使用mmap()创建一个"共享文件映射"
*/
int main(int argc, char *argv[]) {
    char *addr;
    int fd;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file [new-value]\n", argv[0]);
    //以"读写"方式打开"命令行第一个参数指定的文件"
    fd = open(argv[1], O_RDWR);
    if (fd == -1)
        errExit("open");
    //创建新的共享文件映射
    addr = mmap(NULL, 
                MEM_SIZE,//映射长度为10个字节
                PROT_READ | PROT_WRITE, //该区域可读写
                MAP_SHARED,//共享方式
                fd, 0/*从文件头开始映射*/);
    if (addr == MAP_FAILED)//失败
        errExit("mmap");
    //关闭文件
    if (close(fd) == -1) /* No longer need 'fd' */
        errExit("close");
    //从addr地址开始只输出10个字符
    printf("Current string=%.*s\n", MEM_SIZE/*替换前面的星号*/, addr);
    /* 
        Secure practice: output at most MEM_SIZE bytes 
        安全实践:最多输出MEM_SIZE字节
    */

    /* Update contents of region 更新区域内容*/
    if (argc > 2) {
        //不能超过10个字符
        if (strlen(argv[2]) >= MEM_SIZE)
            cmdLineErr("'new-value' too large\n");
        /* Zero out region 区域清0*/
        memset(addr, 0, MEM_SIZE);
        //把"命令行第2个参数传进来的字符串"复制9个字符到"共享文件映射"区域中
        strncpy(addr, argv[2], MEM_SIZE - 1);
        //同步写到底层文件中
        if (msync(addr, MEM_SIZE, MS_SYNC) == -1)
            errExit("msync");
        //标准输出
        printf("Copied \"%s\" to shared memory\n", argv[2]);
    }

    exit(EXIT_SUCCESS);
}
