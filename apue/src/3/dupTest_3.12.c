#include "apue.h"
#include <stdio.h>
 #include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// 测试dup和dup2
int main(void) {
    int work_dir;
    printf("********1.起始信息******\n");
    work_dir = open(_BIN_DIR,O_RDONLY);
    int fd = openat(work_dir,"a.txt",O_CREAT|O_EXCL,FILE_MODE);
    if(fd == -1) {
        fd = openat(work_dir,"a.txt",O_RDWR|O_APPEND);
    }
    printf("open函数调用:fd=%d;FD_CLOEXEC=%d\n",fd,fcntl(fd, F_GETFD));

    fcntl(fd, F_SETFD, 1);
    printf("fcntl函数setfd为1:FD_CLOEXEC=%d\n",fcntl(fd, F_GETFD));

    printf("\n********2.dup******\n");
    int dupfd = dup(fd);
    printf("dup函数:fd=%d;FD_CLOEXEC=%d\n",fd,fcntl(fd, F_GETFD));
    //dup返回的新fd一定是当前可用fd中的最小数值,且FD_CLOEXEC为关闭状态(0)
    printf("dup函数:dupfd=%d;FD_CLOEXEC=%d\n",dupfd,fcntl(dupfd, F_GETFD));

    printf("\n********3_1:dup2: fd2=fd 且 fd为使用(有效)状态 ******\n");
    int dup2fd_equal = dup2(fd, fd);
    printf("dup2函数:fd=%d;FD_CLOEXEC=%d\n",fd,fcntl(fd, F_GETFD));
    // fd2==fd 且 fd有效时: "参数fd"的"fd标志"不改变
    printf("dup2函数:dup2fd_equal=%d;FD_CLOEXEC=%d\n",
                dup2fd_equal,
                fcntl(dup2fd_equal, F_GETFD));

    printf("\n********3_2.dup2: fd2=fd 且 fd为未使用(无效)状态 ******\n");
    int dup2fd_equal_unused = dup2(111, 111);
    printf("dup2函数:fd=%d;FD_CLOEXEC=%d\n",111,fcntl(111, F_GETFD));
    // fd2==fd 且 fd未使用(无效)时: 此时为错误情况(dup2fd_equal_unused为-1，FD_CLOEXEC也为-1)
    printf("dup2函数:dup2fd_equal_unused=%d;FD_CLOEXEC=%d\n",
                dup2fd_equal_unused,
                fcntl(dup2fd_equal_unused, F_GETFD));

    printf("\n********4_1.dup2:fd2!=fd 且 fd2无效 *************\n");
    int dup2fd_not_equal_unused = dup2(fd,999);
    //原来fd的FD_CLOEXEC不变
    printf("dup2函数:fd=%d;FD_CLOEXEC=%d\n",fd,fcntl(fd, F_GETFD));
    //fd2!=fd且fd2未使用(无效)时: 返回的fd的文件描述符标志FD_CLOEXEC会被清除(0)
    printf("dup2函数:dup2fd_not_equal=%d;FD_CLOEXEC=%d\n",
                dup2fd_not_equal_unused,
                fcntl(dup2fd_not_equal_unused, F_GETFD));
    
    printf("********4_2.dup2:fd2!=fd 且 fd2有效(已打开) ******\n");
    if(write(fd,"write to txt\n",13) != 13) {}
    //复制"标准输出"的fd(1),并指定返回为fd(a.txt)，此时dup2fd_not_equal_used指向了1
    int dup2fd_not_equal_used = dup2(1,fd);
    //此时参数fd2(a.txt文件)是已经打开，那么先将其关闭，且FD_CLOEXEC=0(被清除)
    printf("dup2函数:fd=%d;FD_CLOEXEC=%d\n",fd,fcntl(fd, F_GETFD));
    printf("dup2函数:dup2fd_not_equal_used=%d;FD_CLOEXEC=%d\n",
            dup2fd_not_equal_used,
            fcntl(dup2fd_not_equal_used, F_GETFD));
    //fd被重定向了，不再写入文件了，改成了在标准输出显示            
    if(write(fd,"can't write to txt",18) != 18) {//标准输出
        printf("写入fd失败！\n");
    }
    printf("\n");
    if(write(dup2fd_not_equal_used,"222",3) != 3) {//标准输出
        printf("写入dup2fd_not_equal_used失败！\n");
    }
    printf("\n");
	exit(0);
}
