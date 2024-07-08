#include "apue.h"
#ifdef LINUX
#include <sys/sysmacros.h>
#endif
//图4-25:为每个命令行参数打印st_dev的主、次设备号;
//       如果是字符特殊文件或块特殊文件，则打印st_rdev的主、次设备号
int main(int argc, char *argv[]) {
	int			i;
	struct stat	buf;
	//遍历参数
	for (i = 1; i < argc; i++) {
		//打印参数
		printf("%s: ", argv[i]);
		//取文件信息
		if (stat(argv[i], &buf) < 0) {
			err_ret("stat error");
			continue;
		}
		//取st_dev字段的主、次设备号
		printf("dev = %d/%d", major(buf.st_dev),  minor(buf.st_dev));
		//该文件是"字符特殊文件"或"块特殊文件"时
		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
			//打印rdev字段的主、次设备号
			printf(" (%s) rdev = %d/%d",
					(S_ISCHR(buf.st_mode)) ? "character" : "block",
					major(buf.st_rdev), minor(buf.st_rdev));
		}
		printf("\n");
	}
	exit(0);
}

