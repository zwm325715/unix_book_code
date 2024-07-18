#include "apue.h"

//图4-12修改foo和bar两个文件(上一节生成)的访问权限
int main(void) {
	struct stat		statbuf;

	/* 
		turn on set-group-ID and turn off group-execute 
		打开"设置组ID" 并且 关闭"组执行"
		相对于当前状态设置权限
	*/
	//取foo文件的信息(-rw-rw-rw-):4.8节的程序生成的文件
	if (stat("foo", &statbuf) < 0)
		err_sys("stat error for foo");
	//改foo文件的访问权限为:-rw-rwsrw-
	//本实现是基于源文件权限的基础上，还可以用类似下面的所有权限都写一遍
	if (chmod("foo",
		(statbuf.st_mode & ~S_IXGRP)/*关组执行权限*/ 
		| S_ISGID /*执行时设置组ID*/) < 0)
		err_sys("chmod error for foo");

	/* 
		set absolute mode to "rw-r--r--"  
		设置绝对权限值:不关心当前权限位
	*/
	//原文件权限:-rw-------
	//修改为:-rw-r--r--
	if (chmod("bar", 
		S_IRUSR //用户读
		| S_IWUSR //用户写
		| S_IRGRP  //组读
		| S_IROTH /*其他读*/) < 0)
		err_sys("chmod error for bar");

	exit(0);
}
