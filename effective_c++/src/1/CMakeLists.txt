#编译生成的可执行文件放在bin/1目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/1)
add_executable(test
            test.cpp)

                