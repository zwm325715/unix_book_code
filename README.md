# 1.项目

## 简介

 本工程包含了很多经典书上的源码：包括C++以及UNIX相关，未来还会加入linux内核相关

 * 使用cmake构建，代替了make
 * 增加了很多注释
 * 按照章节进行了整理
 * os采用centos7

## 子目录

### apue`(Advanced Programming in the Unix Environment-Third Edition)`

  * 位于apue目录
### tlpi`(The Linux Programming Interface)`
  * 位于tlpi目录

### unpv`(Unix Network Progamming Voume1和2)`
  * 位于unpv目录 
### C++相关
  * c++开头的目录，后缀是书的名字 

# 2.编译命令
* `编译环境`
  * centos操作系统
  * gcc编译器
  * cmake至少3.0以上
* `编译构建`
  * 只拿apue举例，其他都类似
  * 编译所有章节
    * cd apue
    * sh build.sh gen
  * 只编译某一个章节:比如第一章就是1，第2章就是2
    * cd apue
    * sh build.sh gen 1  

* `清除`
  * sh build.sh clean

# 3.目录说明

> 这里只给出了apue的布局，其他书也基本类似

<img src="目录说明.png" style="zoom:100%;" />