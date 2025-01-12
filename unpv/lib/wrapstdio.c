/*
 * Standard I/O wrapper functions.
 */

#include	"unp.h"

void
Fclose(FILE *fp)
{
	if (fclose(fp) != 0)
		err_sys("fclose error");
}

FILE *
Fdopen(int fd, const char *type)
{
	FILE	*fp;

	if ( (fp = fdopen(fd, type)) == NULL)
		err_sys("fdopen error");

	return(fp);
}

char * Fgets(char *ptr, int n, FILE *stream) {
	char	*rptr;
    /*
     * 当遇到文件结束符或错误时,fgets将返回一个空指针：
     *   当返回NULL时通过ferror来检查流是否遇到错误，若是则终止进程，否则返回NULL,
     *   也就是说只是在遇到文件结束符时才返回一个空指针.
     */
	if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		err_sys("fgets error");

	return (rptr);
}

FILE *
Fopen(const char *filename, const char *mode)
{
	FILE	*fp;

	if ( (fp = fopen(filename, mode)) == NULL)
		err_sys("fopen error");

	return(fp);
}

void Fputs(const char *ptr, FILE *stream) {
	if (fputs(ptr, stream) == EOF)
		err_sys("fputs error");
}
