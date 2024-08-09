#编译生成的可执行文件放在bin/14目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/14)
add_executable(nonblockw_14.2
                nonblockw_14.2.c
                $<TARGET_OBJECTS:aque>)
add_executable(deadlock_14.3
                deadlock_14.3.c
                $<TARGET_OBJECTS:aque>)