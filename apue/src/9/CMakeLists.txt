#编译生成的可执行文件放在bin/9目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/9)
add_executable(orphan3_9.10
                orphan3_9.10.c
                $<TARGET_OBJECTS:aque>)