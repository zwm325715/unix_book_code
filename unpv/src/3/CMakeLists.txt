set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/3)
add_executable(byteorder.3-10
                byteorder.3-10.c)
target_link_libraries(byteorder.3-10 PRIVATE unp)
