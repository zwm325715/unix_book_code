#编译生成的可执行文件放在bin/10目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/10)
add_executable(sigusr_10.3
                sigusr_10.3.c
                $<TARGET_OBJECTS:aque>)
add_executable(reenter_10.6
                reenter_10.6.c
                $<TARGET_OBJECTS:aque>)
add_executable(child_10.7
                child_10.7.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(tsleep2_10.10
                tsleep2_10.10.c sleep2_10.10.c
                $<TARGET_OBJECTS:aque>)
add_executable(read1_10.10
                read1_10.10.c
                $<TARGET_OBJECTS:aque>)
add_executable(read2_10.10
                read2_10.10.c
                $<TARGET_OBJECTS:aque>)                
                
add_executable(critical_10.13
                critical_10.13.c
                $<TARGET_OBJECTS:aque>) 

