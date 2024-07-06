#编译生成的可执行文件放在bin/4目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/4)
add_executable(filetype_4.3
                filetype_4.3.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(access_4.7
                access_4.7.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(umask.4.8
                umask.4.8.c
                $<TARGET_OBJECTS:aque>)

add_executable(changemod.4.9
                changemod.4.9.c
                $<TARGET_OBJECTS:aque>)
