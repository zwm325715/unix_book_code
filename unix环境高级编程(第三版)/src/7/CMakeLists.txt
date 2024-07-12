#编译生成的可执行文件放在bin/7目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/7)
add_executable(doatexit_7.3
                doatexit_7.3.c
                $<TARGET_OBJECTS:aque>)
