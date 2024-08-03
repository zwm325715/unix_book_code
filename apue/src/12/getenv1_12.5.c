#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ	4096

//静态缓冲区
static char envbuf[MAXSTRINGSZ];
//全局变量
extern char **environ;
//图12-11 getenv的非可重入版本
char * getenv(const char *name) {
	int i, len;

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++) {
		if ((strncmp(name, environ[i], len) == 0) &&
		  (environ[i][len] == '=')) {
			strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
			return(envbuf);
		}
	}
	return(NULL);
}
