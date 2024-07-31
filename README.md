# 1.项目
## apue(Advanced Programming in the Unix Environment-Third Edition)
  * 位于apue目录
  * 原书的代码目录不够清晰，此项目按**章节**整理了各个源码
  * 使用**CMake**现代构建工具代替了书中的make构建工具
  * 源码定制成**linux**的实现
## tlpi(The Linux Programming Interface)
  * 位于tlpi目录
## 编译命令
* `编译环境`
  * centos操作系统
  * gcc编译器
  * cmake至少3.0以上
* `编译构建`
  * 只拿apue举例，tlpi跟它一样
  * 编译所有章节
    * cd apue
    * sh build.sh gen
  * 只编译某一个章节:比如第一章就是1，第2章就是2
    * cd apue
    * sh build.sh gen 1  

* `清除`
  * sh build.sh clean

# 2.目录说明
<img src="目录说明.png" style="zoom:100%;" />