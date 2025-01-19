set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/6)
add_executable(6.4_tcpcli11
        6.4_tcpcli11.c
        6.4_strcliselect01.c)
target_link_libraries(6.4_tcpcli11 PRIVATE unp)

