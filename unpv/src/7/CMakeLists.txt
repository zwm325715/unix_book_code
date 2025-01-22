set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/7)

add_executable(7.3_checkopts
        7.3_checkopts.c)
target_link_libraries(7.3_checkopts PRIVATE unp)
