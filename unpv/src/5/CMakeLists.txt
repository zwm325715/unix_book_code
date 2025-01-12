#编译生成的可执行文件放在bin/3目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/5)
add_executable(tcpserv01_5-2
                tcpserv01_5-2.c)
target_link_libraries(tcpserv01_5-2 PRIVATE unp)

add_executable(tcpcli01_5-4
        tcpcli01_5-4.c)
target_link_libraries(tcpcli01_5-4 PRIVATE unp)

add_executable(tcpserv01_5.9
        sigchldwait_5-7.c
        tcpserv01_5.9.c)
target_link_libraries(tcpserv01_5.9 PRIVATE unp)

add_executable(tcpcli04_5-9
        tcpcli04_5-9.c)
target_link_libraries(tcpcli04_5-9 PRIVATE unp)

add_executable(tcpserv04_5-12
        tcpserv04_5-12.c
        sigchldwaitpid_5-11.c)
target_link_libraries(tcpserv04_5-12 PRIVATE unp)

add_executable(5.13_tcpcli11
        5.13_tcpcli11.c
        5.13_str_cli11.c)
target_link_libraries(5.13_tcpcli11 PRIVATE unp)