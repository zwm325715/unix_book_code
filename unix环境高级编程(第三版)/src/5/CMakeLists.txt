#编译生成的可执行文件放在bin/5目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/5)
add_executable(getcputc_5.8
                getcputc_5.8.c
                $<TARGET_OBJECTS:aque>)
add_executable(fgetsfputs_5.8
                fgetsfputs_5.8.c
                $<TARGET_OBJECTS:aque>)          