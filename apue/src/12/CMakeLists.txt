#编译生成的可执行文件放在bin/12目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/12)
add_executable(suspend_12.8
                suspend_12.8.c
                $<TARGET_OBJECTS:aque>)
target_link_libraries(suspend_12.8 PRIVATE -lpthread)


add_executable(atfork_12.9
                atfork_12.9.c
                $<TARGET_OBJECTS:aque>)
target_link_libraries(atfork_12.9 PRIVATE -lpthread)