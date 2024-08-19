/* mmcat.c
   Use mmap() plus write() to display the contents of a file (specified
   as a command-line argument) on standard output.
*/
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

/* 
    Listing 49-1 
    使用mmap()来创建一个私有文件映射：
      是一个简单版本的cat(1):将命令行参数指定的整个文件的内容写入到标准输出中
*/
int main(int argc, char *argv[]) {
    char *addr;
    int fd;
    struct stat sb;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);
    //只读打开文件：命令行输入的第一个参数
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("open");

    /*  
       Obtain the size of the file and use it to specify the size of
       the mapping and the size of the buffer to be written 
       获得文件的大小 并用它来指定映射的大小以及写入缓冲区的大小
    */
    if (fstat(fd, &sb) == -1) //取fd背后文件的信息，放到sb中
        errExit("fstat");

    /* 
       Handle zero-length file specially, since specifying a size of
       zero to mmap() will fail with the error EINVAL 
       特别处理零长度文件，因为向mmap()指定大小为0时将失败，并报错EINVAL
    */
    if (sb.st_size == 0) //文件大小为0时
        exit(EXIT_SUCCESS);
    //内存映射:整个文件
    addr = mmap(NULL, //不指定起始地址
                sb.st_size, //映射的字节数:文件大小
                PROT_READ, //区域内容可读
                MAP_PRIVATE, //私有映射
                fd,//文件映射的fd
                0/*从文件开始处映射*/);
    if (addr == MAP_FAILED)//映射失败时
        errExit("mmap");
    //区域内容(文件内容)写到标准输出
    if (write(STDOUT_FILENO, addr, sb.st_size) != sb.st_size)
        fatal("partial/failed write");
    exit(EXIT_SUCCESS);
}
