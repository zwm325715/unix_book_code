add_executable(1_ls1 
                1/ls1.c 
                $<TARGET_OBJECTS:aque>)
add_executable(mycat_1.5.3
                1/mycat_1.5.3.c 
                $<TARGET_OBJECTS:aque>)                
#cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..