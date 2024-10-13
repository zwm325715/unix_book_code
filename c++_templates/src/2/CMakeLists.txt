#编译生成的可执行文件放在bin/2目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/2)
add_executable(deduce1_2.9
                deduce1_2.9.cpp)
add_executable(deduce2_2.9
                deduce2_2.9.cpp)
add_executable(deduce3_2.9
                deduce3_2.9.cpp)                