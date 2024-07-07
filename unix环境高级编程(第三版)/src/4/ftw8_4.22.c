#include "apue.h"
#include <dirent.h>
#include <limits.h>

/* 
	function type that is called for each filename 
	普通函数类型的别名:每一个文件名都会被调用
*/
typedef	int	Myfunc(const char *, const struct stat *, int);
//全局函数变量myfunc
static Myfunc	myfunc;
static int		myftw(char *, Myfunc *);
static int		dopath(Myfunc *);
//统计各种类型的文件的变量
static long	nreg, ndir/*目录个数*/, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]) {
	int		ret;

	if (argc != 2)
		err_quit("usage:  ftw  <starting-pathname>");
	
	ret = myftw(argv[1], myfunc/*下面的myfunc函数*/);		/* does it all */
	//总数
	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if (ntot == 0)
		ntot = 1;		/* avoid divide by 0; print 0 for all counts */
	printf("regular files  = %7ld, %5.2f %%\n", nreg,
	  nreg*100.0/ntot);
	printf("directories    = %7ld, %5.2f %%\n", ndir,
	  ndir*100.0/ntot);
	printf("block special  = %7ld, %5.2f %%\n", nblk,
	  nblk*100.0/ntot);
	printf("char special   = %7ld, %5.2f %%\n", nchr,
	  nchr*100.0/ntot);
	printf("FIFOs          = %7ld, %5.2f %%\n", nfifo,
	  nfifo*100.0/ntot);
	printf("symbolic links = %7ld, %5.2f %%\n", nslink,
	  nslink*100.0/ntot);
	printf("sockets        = %7ld, %5.2f %%\n", nsock,
	  nsock*100.0/ntot);
	exit(ret);
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */
#define	FTW_F	1		/* file other than directory 非目录文件 */
#define	FTW_D	2		/* directory 目录*/
#define	FTW_DNR	3		/* directory that can't be read */
#define	FTW_NS	4		/*lstat出错了:file that we can't stat  */
//堆内存起始地址:存储了main传递进来的"目录字符串"
static char	*fullpath;		/* contains full pathname for every file */
//上面fullpath内存的字节长度
static size_t pathlen;

/* we return whatever func() returns */
static int myftw(char *pathname, Myfunc *func) {
	/* malloc PATH_MAX+1 bytes 分配内存*/
	fullpath = path_alloc(&pathlen);	
	//分配的长度 小于 入参的路径时
	if (pathlen <= strlen(pathname)) {
		//2倍扩容再分配
		pathlen = strlen(pathname) * 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL)
			err_sys("realloc failed");
	}
	//把目录名复制进去
	strcpy(fullpath, pathname);
	return(dopath(func));
}

/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return.  For a directory, we call ourself
 * recursively for each name in the directory.
 */
/* we return whatever func() returns */
static int dopath(Myfunc* func) {
	struct stat		statbuf;//目录信息
	struct dirent	*dirp;
	DIR				*dp;
	int				ret, n;
	//查询该目录的信息，丢到statbuf中
	if (lstat(fullpath, &statbuf) < 0)	/* stat error */
		//lstat出错了
		return(func(fullpath, &statbuf, FTW_NS));
	//该文件不是目录时
	if (S_ISDIR(statbuf.st_mode) == 0)	/* not a directory */
		//非目录时
		return(func(fullpath, &statbuf, FTW_F));
	//走到这里就是目录了：调用myfunc函数去做统计
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)//目录时，返回值为0
		return(ret);
	//取目录字符串长度(不包含尾零)
	n = strlen(fullpath);
	//内存需要扩容时
	if (n + NAME_MAX + 2 > pathlen) {	/* expand path buffer */
		pathlen *= 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL)
			err_sys("realloc failed");
	}
	//目录字符串追加'/'后，n值自增1
	fullpath[n++] = '/';
	//放尾零0
	fullpath[n] = 0;
	//打开目录fullpath，返回DIR结构
	if ((dp = opendir(fullpath)) == NULL)	/* can't read directory */
		//不能打开opendir
		return(func(fullpath, &statbuf, FTW_DNR));
	//循环读取fullpath目录中的目录项(目录中的文件、子目录等)
	while ((dirp = readdir(dp)) != NULL) {
		//如果是"."和".."目录项，就跳过
		if (strcmp(dirp->d_name, ".") == 0  ||
		    strcmp(dirp->d_name, "..") == 0)
				continue;		/* ignore dot and dot-dot */
		//追加该目录项的名字
		strcpy(&fullpath[n], dirp->d_name);	/* append name after "/" */
		//递归读
		if ((ret = dopath(func)) != 0)		/* recursive */
			break;	/* time to leave */
	}
	//
	/* 
		erase everything from slash onward 
		删除从斜杠开始的所有内容:目的是可以复用
	*/
	fullpath[n-1] = 0;	
	//关闭opendir打开的这个目录
	if (closedir(dp) < 0)
		err_ret("can't close directory %s", fullpath);
	return(ret);
}

static int myfunc(const char *pathname, 
				 const struct stat *statptr, 
				 int type/*类型:FTW_D(目录)*/) {
	switch (type) {
		//非目录文件
		case FTW_F:
			/*
				早期的UNIX版本并不提供S_ISxxx宏，
				于是就需要将st_mode与屏蔽字S_IFMT进行逻辑与运算,
				然后与名为S_IFxxx的常量相比较。
			*/
			switch (statptr->st_mode & S_IFMT) {
				case S_IFREG:	nreg++;		break;//普通文件
				case S_IFBLK:	nblk++;		break;//块特殊文件
				case S_IFCHR:	nchr++;		break;//字符特殊文件
				case S_IFIFO:	nfifo++;	break;//命名管道文件
				case S_IFLNK:	nslink++;	break;//符号链接文件
				case S_IFSOCK:	nsock++;	break;//套接字
				/*此时不应该出现目录 directories should have type = FTW_D */
				case S_IFDIR:	
					err_dump("for S_IFDIR for %s", pathname);
			}
			break;
		//目录
		case FTW_D:
			ndir++;//自增1
			break;
		case FTW_DNR://不能打开该目录:opendir报错
			err_ret("can't read directory %s", pathname);
			break;
		case FTW_NS://lstat函数出错了
			err_ret("stat error for %s", pathname);
			break;
		default:
			err_dump("unknown type %d for pathname %s", type, pathname);
	}
	return(0);
}
