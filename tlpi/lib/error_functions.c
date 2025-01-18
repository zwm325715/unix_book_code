#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"          /* Defines ename and MAX_ENAME */

//终止进程
NORETURN static void terminate(Boolean useExit3) {
    char *s;
    //获取环境变量EF_DUMPCORE的值
    s = getenv("EF_DUMPCORE");
    //有值时
    if (s != NULL && *s != '\0') {
        abort();//终止进程:产生SIGABRT信号和core文件
    } else if (useExit3) {
        //标准IO库打开的流执行close后再正常终止进程:ISO C标准
        exit(EXIT_FAILURE);
    } else {
        //不刷新stdio缓冲区也不调用退出处理程序,直接正常终止进程:POSIX 标准
        _exit(EXIT_FAILURE);
    }
}

//可拼接 "errno信息" 和 "可变实参" 字符串到标准错误进行输出
static void outputError(Boolean useErr,//是否使用errno信息
                        int err,//errno错误码
                        Boolean flushStdout,//是否flush标准输出缓冲区
                        const char *format,//错误信息格式
                        va_list ap/*可变参数指针*/) {
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
    //格式化输出到userMsg中
    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if (useErr) {
        //格式化输出到errText中
        snprintf(errText, BUF_SIZE, " [%s %s]",
                //errno错误码的"名字"
                (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?",
                //errno错误码的"描述信息"
                strerror(err));
    } else {
        snprintf(errText, BUF_SIZE, ":");
    }

#if __GNUC__ >= 7
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-truncation"
#endif
    //将errText和userMsg拼接在一起，放到buf中
    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);
#if __GNUC__ >= 7
#pragma GCC diagnostic pop
#endif
    //flush 标准输出时
    if (flushStdout) {
        fflush(stdout);
    }
    fputs(buf, stderr);// 将buf字符串写到标准错误
    fflush(stderr);//flush标准错误
}

/**
 * 1.在标准错误打印消息: "errno信息" 和 "可变参数实参" 拼接起来的字符串
 * 2.进程不终止
 * @param format
 * @param ...
 */
void errMsg(const char *format, ...) {
    va_list argList;//可变参数指针:用来取可变参数列表
    int savedErrno;//保存现场:当前错误码
    savedErrno = errno; /* In case we change it here */
    //初始化可变参数指针
    va_start(argList, format/*最后一个固定参数*/);
    //在标准错误输出:errno和可变参数实参 拼接起来的字符串
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);//终止可变参数
    //恢复errno
    errno = savedErrno;
}

/**
 * 1.在标准错误打印消息: "errno信息" 和 "可变参数实参" 拼接起来的字符串
 * 2.进程终止
 * @param format
 * @param ...
 */
void errExit(const char *format, ...) {
    va_list argList;
    //1.这里的逻辑同errMsg()
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    //2.终止进程：清理IO
    terminate(TRUE);
}

/**
 * 1.功能基本同errExit(),只是有如下不同点:
 *   -不会刷新标准输出
 *   -不刷新stdio缓冲区也不调用退出处理程序
 * 2.常用在fork的子进程因发生错误需要终止时:
 *   避免了对继承了父进程的stdio缓冲区进行刷新，也不会调用父进程所建立的退出处理程序
 * @param format
 * @param ...
 */
void err_exit(const char *format, ...) {
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, FALSE/*不刷新stdout*/, format, argList);
    va_end(argList);
    //_exit:不刷新stdio缓冲区也不调用退出处理程序
    terminate(FALSE);
}

/**
 * 功能类似errExit():
 *   只是增加了errnum参数，而不是取自errno
 * @param errnum
 * @param format
 * @param ...
 */
void errExitEN(int errnum, const char *format, ...) {
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errnum/*实参*/, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}


void fatal(const char *format, ...) {
    va_list argList;

    va_start(argList, format);
    outputError(FALSE/*无errno信息*/, 0, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

//诊断命令行参数使用方面的错误
void usageErr(const char *format, ...) {
    va_list argList;
    //刷新stdout
    fflush(stdout);
    //标准错误输出Usage:
    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    //刷新stderr
    fflush(stderr);
    //终止进程:flush
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...) {
    va_list argList;

    fflush(stdout);

    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);           /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}
