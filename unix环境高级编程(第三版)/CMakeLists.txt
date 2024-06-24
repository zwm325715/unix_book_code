# 版本 cmake --version来查看当前安装的cmake版本
cmake_minimum_required(VERSION 3.0)

project(TESTCMAKE)

#debug参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
#debug
set(CMAKE_BUILD_TYPE Debug)