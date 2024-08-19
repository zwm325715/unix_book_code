#编译生成的可执行文件放在bin/49目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/49)
add_executable(mmcat_49.2
                mmcat_49.2.c
                $<TARGET_OBJECTS:tlpi>)
               