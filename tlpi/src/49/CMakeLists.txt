#编译生成的可执行文件放在bin/49目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/49)
add_executable(mmcat_49.2
                mmcat_49.2.c
                $<TARGET_OBJECTS:tlpi>)

#执行这个程序需要创建一个文件，参考命令dd
add_executable(t_mmap_49.4.2
                t_mmap_49.4.2.c
                $<TARGET_OBJECTS:tlpi>)
                

add_executable(anon_mmap_49.7
                anon_mmap_49.7.c
                $<TARGET_OBJECTS:tlpi>)