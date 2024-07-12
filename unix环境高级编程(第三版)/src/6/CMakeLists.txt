#编译生成的可执行文件放在bin/6目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/6)
add_executable(getpwnam_6.2
                getpwnam_6.2.c
                $<TARGET_OBJECTS:aque>)

add_executable(strftime_6.11
                strftime_6.11.c
                $<TARGET_OBJECTS:aque>)

add_executable(getpwsvr4_exercise.2
                getpwsvr4_exercise.2.c
                $<TARGET_OBJECTS:aque>)

add_executable(prtime_exercise.3
                prtime_exercise.3.c
                $<TARGET_OBJECTS:aque>)
                