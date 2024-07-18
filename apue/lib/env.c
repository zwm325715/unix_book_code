#include "apue.h"

//新增PATH环境变量
int append_env_PATH(char *newPath) {
    // 获取当前PATH值
    const char *getPath = getenv("PATH");
    if (getPath != NULL) {
        // 拼接新值和旧值
        size_t len = strlen(getPath) + strlen(newPath) + 2;
        char *mergedPath = malloc(len);
        if (mergedPath != NULL) {
            snprintf(mergedPath, len, "%s:%s", newPath, getPath);
            // 设置新的PATH值
            setenv("PATH", mergedPath, 1);
            free(mergedPath);
        }
    }
 
    return 0;
}
