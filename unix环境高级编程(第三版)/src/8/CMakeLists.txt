#编译生成的可执行文件放在bin/8目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/8)
add_executable(fork1_8.3
                fork1_8.3.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(vfork1_8.4
                vfork1_8.4.c
                $<TARGET_OBJECTS:aque>)

add_executable(wait1_8.6
                wait1_8.6.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(fork2_8.6
                fork2_8.6.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(tellwait1_8.9
                tellwait1_8.9.c
                $<TARGET_OBJECTS:aque>)

add_executable(tellwait2_8.9
                tellwait2_8.9.c
                $<TARGET_OBJECTS:aque>)

add_executable(echoall_8.10
                echoall_8.10.c
                $<TARGET_OBJECTS:aque>)      
add_executable(exec1_8.10
                exec1_8.10.c    
                $<TARGET_OBJECTS:aque>)
target_compile_definitions(exec1_8 PRIVATE "ROOT_DIR=${CMAKE_SOURCE_DIR}/bin/8") 
