#include "apue.h"
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

//图3-2:创建一个具有空洞的文件
int main(void) {
	int		fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");

	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");
	/* offset now = 10 */
	
	//文件当前长度为10，但是lseek定位的"偏移量(16384)"超过了文件的"当前长度",
	//此时满足了产生空洞的条件
	if (lseek(fd, 16384, SEEK_SET) == -1)  
		err_sys("lseek error");
	/* offset now = 16384 */

	//对该文件执行写时将加长该文件，并构成了"空洞".
	//注意此时是可以写入成功的
	if (write(fd, buf2, 10) != 10) 
		err_sys("buf2 write error");
	/* offset now = 16394 */

	exit(0);
}
