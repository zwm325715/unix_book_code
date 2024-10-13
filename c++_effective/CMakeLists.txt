# 版本 cmake --version来查看当前安装的cmake版本
cmake_minimum_required(VERSION 3.0)

execute_process(COMMAND which gcc COMMAND tr -d '\n' OUTPUT_VARIABLE GCC_BIN)
set(CMAKE_C_COMPILER ${GCC_BIN})
message (SATUS " gcc compiler path=${CMAKE_C_COMPILER}!")
execute_process(COMMAND which g++ COMMAND tr -d '\n' OUTPUT_VARIABLE GPLUS_BIN)
set(CMAKE_CXX_COMPILER ${GPLUS_BIN})
message (SATUS " g++ compiler path=${CMAKE_CXX_COMPILER}!")

project(C++_Primer
        VERSION 1.0.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#头文件搜索目录
# include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/lib)

# add_subdirectory(lib)
add_subdirectory(src)