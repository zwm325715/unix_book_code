#编译生成的可执行文件放在bin/3目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/3)
add_executable(seek
                seek.c
                $<TARGET_OBJECTS:aque>)
add_executable(hole
                hole.c
                $<TARGET_OBJECTS:aque>)
add_executable(nohole
                nohole.c 
                $<TARGET_OBJECTS:aque>)
add_executable(sus_lp64Offset
                sus_lp64Offset.c
                $<TARGET_OBJECTS:aque>)
                
                         