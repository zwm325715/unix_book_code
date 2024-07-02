#include "apue.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//SUS标准通过sysconf函数确定支持何种环境
int main(void) {
	long	val;
    //--------------32位--------------
	printf("1.errno= %d\n", errno);
	//调用sysconf函数获取_SC_V7_ILP32_OFF32配置
	if ((val = sysconf(_SC_V7_ILP32_OFF32)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs("_SC_V7_ILP32_OFF32 (not supported)\n", stdout);
			else
				err_sys("sysconf _SC_V7_ILP32_OFF32 error");
		} else {
			fputs("_SC_V7_ILP32_OFF32 (no limit)\n", stdout);
		}
	} else {
		printf("_SC_V7_ILP32_OFF32常量的值: %ld\n", val);
	}

	printf("2.errno= %d\n", errno);
    //调用sysconf函数获取_SC_V7_ILP32_OFFBIG配置
	if ((val = sysconf(_SC_V7_ILP32_OFFBIG)) < 0) {
        if (errno != 0) {
			if (errno == EINVAL)
				fputs("_SC_V7_ILP32_OFFBIG (not supported)\n", stdout);
			else
				err_sys("sysconf _SC_V7_ILP32_OFFBIG error");
		} else {
			fputs("_SC_V7_ILP32_OFFBIG (no limit)\n", stdout);
		}
	} else {
		printf("_SC_V7_ILP32_OFFBIG常量的值: %ld\n", val);
	}

    //--------------64位甚至更大----------------
	printf("3.errno= %d\n", errno);
	//调用sysconf函数获取_SC_V7_LP64_OFF64配置
	if ((val = sysconf(_SC_V7_LP64_OFF64)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs("_SC_V7_LP64_OFF64 (not supported)\n", stdout);
			else
				err_sys("sysconf _SC_V7_LP64_OFF64 error");
		} else {
			fputs("_SC_V7_LP64_OFF64 (no limit)\n", stdout);
		}
	} else {
		printf("_SC_V7_LP64_OFF64常量的值: %ld\n", val);
	}
	printf("4.errno= %d\n", errno);
    //没有_SC_V7_LP64_OFFBIG，变成了_SC_V7_LPBIG_OFFBIG
	if ((val = sysconf(_SC_V7_LPBIG_OFFBIG)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs("_SC_V7_LPBIG_OFFBIG (not supported)\n", stdout);
			else
				err_sys("sysconf _SC_V7_LPBIG_OFFBIG error");
		} else {
			fputs("_SC_V7_LPBIG_OFFBIG (no limit)\n", stdout);
		}
	} else {
		printf("_SC_V7_LPBIG_OFFBIG常量的值: %ld\n", val);
	}
	printf("5.errno= %d\n", errno);
    exit(0);
}