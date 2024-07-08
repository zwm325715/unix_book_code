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

add_executable(unlink.4.15
                unlink.4.15.c
                $<TARGET_OBJECTS:aque>)                

add_executable(zap.4.20
                zap.4.20.c
                $<TARGET_OBJECTS:aque>)

add_executable(ftw8_4.22
                ftw8_4.22.c
                $<TARGET_OBJECTS:aque>)

add_executable(mycd_4.23
                mycd_4.23.c
                $<TARGET_OBJECTS:aque>)
add_executable(cdpwd_4.23
                cdpwd_4.23.c
                $<TARGET_OBJECTS:aque>)

add_executable(devrdev_4.24
                devrdev_4.24.c
                $<TARGET_OBJECTS:aque>)
                                