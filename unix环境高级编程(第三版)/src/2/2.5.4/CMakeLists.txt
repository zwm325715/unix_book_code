#grep -v "^#" sysconf-lim.sym >sysconf.sym
execute_process(COMMAND grep -v "^#" sysconf-lim.sym 
                #当前目录下执行命令grep
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_FILE sysconf.sym
                RESULT_VARIABLE SYSCONF_GREP_RES)
if(${SYSCONF_GREP_RES} EQUAL 0) 
    message (SATUS " ---sysconf-lim.sym输出到sysconf.sym成功!")
else()
    message (FATAL_ERROR "sysconf-lim.sym输出到sysconf.sym失败!")
endif()
#grep -v "^#" pathconf-lim.sym >pathconf.sym
execute_process(COMMAND grep -v "^#" pathconf-lim.sym
                #当前目录下执行命令grep
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_FILE pathconf.sym
                RESULT_VARIABLE PATHCONF_GREP_RES)
if(${PATHCONF_GREP_RES} EQUAL 0) 
    message (SATUS " ---pathconf-lim.sym输出到pathconf.sym成功!")
else()
    message (FATAL_ERROR "pathconf-lim.sym输出到pathconf.sym失败!")
endif()

#awk -f makeconf.awk >conf.c
execute_process(COMMAND awk -f makeconf.awk
                #当前目录下执行命令grep
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_FILE conf.c
                RESULT_VARIABLE AWK_GEN_RES)
if(${AWK_GEN_RES} EQUAL 0) 
    message (SATUS " ---awk生成conf.c成功!")
else()
    message (FATAL_ERROR "awk生成conf.c失败!")
endif()

add_executable(conf_2.5.4
                conf.c 
                $<TARGET_OBJECTS:aque>)