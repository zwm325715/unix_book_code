#编译生成的可执行文件放在bin/1目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/1)
add_executable(daytimetcpcli_1-5
                daytimetcpcli_1-5.c)
target_link_libraries(daytimetcpcli_1-5 PRIVATE unp)

add_executable(daytimetcpcliv6_1-6
        daytimetcpcliv6_1-6.c)
target_link_libraries(daytimetcpcliv6_1-6 PRIVATE unp)
