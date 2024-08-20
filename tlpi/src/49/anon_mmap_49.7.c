/* anon_mmap.c
   Demonstrate how to share a region of mapped memory between a parent and
   child process without having to create a mapped file, either through the
   creation of an anonymous memory mapping or through the mapping of /dev/zero.
*/
#ifdef USE_MAP_ANON
#define _BSD_SOURCE   /* Get MAP_ANONYMOUS definition */
#endif
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

/* 
    Listing 49-3 
    1.使用MAP_ANONYMOUS或/dev/zero技术在父子进程之间共享一个映射区域
        使用哪一种由USE_MAP_ANON宏(编译时指定)来决定
*/
int main(int argc, char *argv[]) {
    /* Pointer to shared memory region */
    int *addr;                  

    /* Parent creates mapped region prior to calling fork() */
/* Use MAP_ANONYMOUS 第一种技术*/    
#ifdef USE_MAP_ANON
    //创建共享匿名映射:只存int
    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
#else /* Map /dev/zero 第2种技术*/
    int fd;

    fd = open("/dev/zero", O_RDWR);
    if (fd == -1)
        errExit("open");

    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
    //关闭fd
    if (close(fd) == -1) /* No longer needed */       
        errExit("close");
#endif
    //往映射区域写数据:1
    *addr = 1; /* Initialize integer in mapped region */
    /* Parent and child share mapping 父子进程共享映射*/
    switch (fork()) {//创建子进程
    case -1:
        errExit("fork");
    /* Child: increment shared integer and exit */
    case 0://子进程执行
        printf("Child started, value = %d\n", *addr);
        (*addr)++;//自增1
        //取消映射
        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");
        exit(EXIT_SUCCESS);//子进程退出
    /* Parent: wait for child to terminate */        
    default:  //父进程执行
        //等待子进程退出
        if (wait(NULL) == -1)
            errExit("wait");
        printf("In parent, value = %d\n", *addr);
        //取消映射
        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");
        exit(EXIT_SUCCESS);
    }
}
