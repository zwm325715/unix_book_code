# 版本 cmake --version来查看当前安装的cmake版本
cmake_minimum_required(VERSION 3.8)
#支持c++17:需自己调整路径
set(CMAKE_C_COMPILER "/usr/local/soft/gcc9.4.0/bin/gcc")
message (SATUS " gcc compiler path=${CMAKE_C_COMPILER}!")
set(CMAKE_CXX_COMPILER "/usr/local/soft/gcc9.4.0/bin/g++")
message (SATUS " g++ compiler path=${CMAKE_CXX_COMPILER}!")

project(C++_modern
        VERSION 1.0.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)