#编译生成的可执行文件放在bin/2目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/2)
# add_executable(ls1_1.4.3
#                 ls1_1.4.3.c 
#                 $<TARGET_OBJECTS:aque>)

add_subdirectory(2.5.4)