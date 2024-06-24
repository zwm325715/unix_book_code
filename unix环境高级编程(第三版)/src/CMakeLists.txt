add_executable(main_1_ls1 
                1/ls1.c 
                $<TARGET_OBJECTS:aque>)
#cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..