#编译生成的可执行文件放在bin/3目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/4)
add_executable(daytimetcpsrv1_4-11
                daytimetcpsrv1_4-11.c)
target_link_libraries(daytimetcpsrv1_4-11 PRIVATE unp)
