#############################生成conf.c################################
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
                RESULT_VARIABLE AWK_GEN_CONF_RES)
if(${AWK_GEN_CONF_RES} EQUAL 0) 
    message (SATUS " ---awk生成conf.c成功!")
else()
    message (FATAL_ERROR "awk生成conf.c失败!")
endif()

add_executable(conf_2.5.4
                conf.c 
                $<TARGET_OBJECTS:aque>)
########################生成option.c######################################
#grep -v "^#" sysconf-opt.sym >sysopt.sym
execute_process(COMMAND grep -v "^#" sysconf-opt.sym
                #当前目录下执行命令grep
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_FILE sysopt.sym
                RESULT_VARIABLE SYSOPT_GREP_RES)
if(${SYSOPT_GREP_RES} EQUAL 0) 
    message (SATUS " ---sysconf-opt.sym 输出到sysopt.sym成功!")
else()
    message (FATAL_ERROR "sysconf-opt.sym 输出到sysopt.sym失败!")
endif()
#grep -v "^#" pathconf-opt.sym >pathopt.sym
execute_process(COMMAND grep -v "^#" pathconf-opt.sym
                #当前目录下执行命令grep
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_FILE pathopt.sym
                RESULT_VARIABLE PATHOPT_GREP_RES)
if(${PATHOPT_GREP_RES} EQUAL 0) 
    message (SATUS " ---pathconf-opt.sym输出到pathopt.sym成功!")
else()
    message (FATAL_ERROR "pathconf-opt.sym输出到pathopt.sym失败!")
endif()

#awk -f makeopt.awk >options.c
execute_process(COMMAND awk -f makeopt.awk
                #当前目录下执行命令grep
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_FILE options.c
                RESULT_VARIABLE AWK_GEN_OPT_RES)
if(${AWK_GEN_OPT_RES} EQUAL 0) 
    message (SATUS " ---awk生成options.c成功!")
else()
    message (FATAL_ERROR "awk生成options.c失败!")
endif()

add_executable(opt_2.5.4
                options.c
                $<TARGET_OBJECTS:aque>)