# 版本 cmake --version来查看当前安装的cmake版本
cmake_minimum_required(VERSION 3.0)

execute_process(COMMAND which gcc COMMAND tr -d '\n' OUTPUT_VARIABLE GCC_BIN)
set(CMAKE_C_COMPILER ${GCC_BIN})

project(UNIX 
        VERSION 1.0.0
        LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLINUX -D_GNU_SOURCE")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#头文件搜索目录
include_directories(${CMAKE_SOURCE_DIR}/include)
#编译生成的可执行文件放在bin目录下
# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(lib)
add_subdirectory(src)