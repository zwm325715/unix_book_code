#编译生成的可执行文件放在bin/3目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/3)
add_executable(seek_3.6
                seek_3.6.c
                $<TARGET_OBJECTS:aque>)
add_executable(hole_3.6
                hole_3.6.c
                $<TARGET_OBJECTS:aque>)
add_executable(nohole_3.6
                nohole_3.6.c 
                $<TARGET_OBJECTS:aque>)
add_executable(sus_lp64Offset_3.6
                sus_lp64Offset_3.6.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(mycat_3.9
                mycat_3.9.c
                $<TARGET_OBJECTS:aque>)                        