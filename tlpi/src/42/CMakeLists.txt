#编译生成的可执行文件放在bin/42目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/42)
add_executable(dynload_42.1
                dynload_42.1.c
                $<TARGET_OBJECTS:tlpi>)
target_link_libraries(dynload_42.1 -ldl)