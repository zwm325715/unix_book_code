#include "apue.h"

#define BSZ 48
// 图5-15给出了用已知模式填充缓冲区时流写入是如何操作的
int main() {
	FILE *fp;
	char buf[BSZ];
	//1.填充46个a字符到buf字符数组中
	memset(buf, 'a', BSZ-2);
	//倒数第2个为尾零(null)
	buf[BSZ-2] = '\0';
	//最后一个为'X'
	buf[BSZ-1] = 'X';
	//读写方式打开(截至0长)buf
	if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
		err_sys("fmemopen failed");
	//因为被截断至0了，所以啥也没有
	printf("initial buffer contents: %s\n", buf);//initial buffer contents:
	//写到buf中
	fprintf(fp, "hello, world");
	//流冲洗后才会变化
	printf("before flush: %s\n", buf);//before flush:
	//执行fflush会往buf中的当前位置写入一个null字节
	fflush(fp);
	printf("after fflush: %s\n", buf);//after fflush: hello, world
	//null字节是加到字符串的结尾
	printf("len of string in buf = %ld\n", 
			(long)strlen(buf));//len of string in buf = 12

	//2.改写缓冲区为'b'字符(只是内容变)
	//注意此时文件偏移量指针并没有动，还是在12个b(原来是hello,world)后的那个位置
	memset(buf, 'b', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	//在第13个位置处开始写(bbbbbbbbbbbbhello, worldbbbbbbbbb...bbb\0X)
	fprintf(fp, "hello, world");
	//fseek定位到文件开始处(offset变了)，并在移动前在当前位置(world后的位置)插入null
	fseek(fp, 0, SEEK_SET);
	printf("after  fseek: %s\n", buf);//after fseek: bbbbbbbbbbbbhello, world
	printf("len of string in buf = %ld\n", 
			(long)strlen(buf));//len of string in buf = 24

	//3.改写缓冲区为'c'字符(只是内容变)，offset并没有变(在文件开头)
	memset(buf, 'c', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "hello, world");//开头写入(offset移动到world后面)
	//调用fclose时(没有在当前位置写入一个null字节)
	fclose(fp);
	//after fclose: hello, worldcccccccccccccccccccccccccccccccccc
	printf("after fclose: %s\n", buf);
	//没有追加null字节
	//len of string in buf = 46
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	return(0);
}
