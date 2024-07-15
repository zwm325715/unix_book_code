#编译生成的可执行文件放在bin/8目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/8)
add_executable(fork1_8.3
                fork1_8.3.c
                $<TARGET_OBJECTS:aque>)
add_executable(vfork1_8.4
                vfork1_8.4.c
                $<TARGET_OBJECTS:aque>)

