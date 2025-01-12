#include	"unp.h"

/*
 * 确定主机字节序
 */
int main(int argc, char **argv) {
  //数
  union {
      short  s;//被赋值
      char   c[sizeof(short)];//按字节从这读取进行判断
  } un;
  //存2个字节，赋值给short类型的s
  un.s = 0x0102;//01为高序字节(MSB),02为低序字节(LSB)

  printf("%s: ", CPU_VENDOR_OS);
  if (sizeof(short) == 2) {
    if (un.c[0] == 1 && un.c[1] == 2) {
      //低地址为1,高地址为2 => 低地址存高序字节 => 大端
      printf("big-endian\n");
    }else if (un.c[0] == 2 && un.c[1] == 1) {
      //低地址为2,高地址为1 => 低地址存低序字节 => 小端
      printf("little-endian\n");
    }else {
      printf("unknown\n");
    }
  } else {
    printf("sizeof(short) = %d\n", sizeof(short));
  }
  
  exit(0);
}
