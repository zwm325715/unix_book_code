set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/6)
add_executable(6.4_tcpcli11
        6.4_tcpcli11.c
        6.4_strcliselect01.c)
target_link_libraries(6.4_tcpcli11 PRIVATE unp)

add_executable(6.7_tcpcli02
        6.7_tcpcli02.c
        6.7_strcliselect02.c)
target_link_libraries(6.7_tcpcli02 PRIVATE unp)


add_executable(6.11_tcpservpoll01
        6.11_tcpservpoll01.c)
target_link_libraries(6.11_tcpservpoll01 PRIVATE unp)
