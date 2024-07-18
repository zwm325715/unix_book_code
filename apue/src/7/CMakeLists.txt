#编译生成的可执行文件放在bin/7目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/7)
add_executable(doatexit_7.3
                doatexit_7.3.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(echoarg_7.4
                echoarg_7.4.c
                $<TARGET_OBJECTS:aque>)

add_executable(testjmp_7.10_no_optimize
                testjmp_7.10.c
                $<TARGET_OBJECTS:aque>)

add_executable(testjmp_7.10_optimize
                testjmp_7.10.c
                $<TARGET_OBJECTS:aque>)
target_compile_options(testjmp_7.10_optimize PRIVATE "-O")

add_executable(getrlimit_7.11
                getrlimit_7.11.c
                $<TARGET_OBJECTS:aque>)
