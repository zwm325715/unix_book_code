#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  ssize_t numRead;
  char buf[BUF_SIZE];

  if (argc != 3 || strcmp(argv[1], "--help") == 0)
    usageErr("%s old-file new-file\n", argv[0]);

  /* Open input and output files */
  inputFd = open(argv[1], O_RDONLY);//打开输入文件
  if (inputFd == -1) {//打开失败
    errExit("opening file %s", argv[1]);
  }

  //输出文件的打开选项
  openFlags = O_CREAT/*不存在就创建*/ |
              O_WRONLY/*只写*/ |
              O_TRUNC/*清空内容*/;
  /*
   * 1.创建输出的文件权限(拥有的权限，当然还要考虑umask的值)，通过下面命令可查看
   *      [ob@localhost 4]$ umask
   *      0002  通常为该值
   * 2.该权限值 跟 ~umask 做逻辑与运算才是最终的文件权限值(可见并没有:其他写)
   *     -rw-rw-r-- 1 ob ob 1825 Jan 21 06:33 output
   */
  filePerms = S_IRUSR | S_IWUSR |
              S_IRGRP | S_IWGRP |
              S_IROTH | S_IWOTH;/* rw-rw-rw- :不一定就是这个权限哦*/
  //打开输出文件
  outputFd = open(argv[2], openFlags, filePerms);
  if (outputFd == -1) {
    errExit("opening file %s", argv[2]);
  }

  /* Transfer data until we encounter end of input or an error */
  //读取数据(注意:缺少了中断处理)
  while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
    //写到输出文件中
    if (write(outputFd, buf, numRead) != numRead) {
      fatal("write() returned error or partial write occurred");
    }
  }

  if (numRead == -1) {
    errExit("read");
  }
  //收尾工作:关闭2个fd
  if (close(inputFd) == -1) {
    errExit("close input");
  }
  if (close(outputFd) == -1) {
    errExit("close output");
  }

  //进程退出
  exit(EXIT_SUCCESS);
}
