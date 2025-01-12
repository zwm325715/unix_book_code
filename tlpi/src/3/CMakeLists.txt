#编译生成的可执行文件放在bin/3目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/3)
 add_executable(3.3_glibc_version
                3.3_glibc_version.c
                 $<TARGET_OBJECTS:tlpi>)
               