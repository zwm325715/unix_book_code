#编译生成的可执行文件放在bin/11目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/11)
add_executable(threadid_11.4
                threadid_11.4.c
                $<TARGET_OBJECTS:aque>)
target_link_libraries(threadid_11.4 PRIVATE -lpthread)

add_executable(exitstatus_11.5
                exitstatus_11.5.c
                $<TARGET_OBJECTS:aque>)
target_link_libraries(exitstatus_11.5 PRIVATE -lpthread)

add_executable(badexit2_11.5
                badexit2_11.5.c
                $<TARGET_OBJECTS:aque>)
target_link_libraries(badexit2_11.5 PRIVATE -lpthread)

add_executable(cleanup_11.5
                cleanup_11.5.c
                $<TARGET_OBJECTS:aque>)
target_link_libraries(cleanup_11.5 PRIVATE -lpthread)

add_executable(timedlock_11.6.3
                timedlock_11.6.3.c
                $<TARGET_OBJECTS:aque>)
target_link_libraries(timedlock_11.6.3 PRIVATE -lpthread)

# add_executable(barrier_11.6.8
#                 barrier_11.6.8.c
#                 $<TARGET_OBJECTS:aque>)
# target_link_libraries(barrier_11.6.8 PRIVATE -lpthread)
