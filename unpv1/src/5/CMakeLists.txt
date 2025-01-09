#编译生成的可执行文件放在bin/3目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/5)
add_executable(tcpserv01_5-2
                tcpserv01_5-2.c)
target_link_libraries(tcpserv01_5-2 PRIVATE unp)

add_executable(tcpcli01_5-4
        tcpcli01_5-4.c)
target_link_libraries(tcpcli01_5-4 PRIVATE unp)