#编译生成的可执行文件放在bin/8目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/8)
add_executable(fork1_8.3
                fork1_8.3.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(vfork1_8.4
                vfork1_8.4.c
                $<TARGET_OBJECTS:aque>)

add_executable(wait1_8.6
                wait1_8.6.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(fork2_8.6
                fork2_8.6.c
                $<TARGET_OBJECTS:aque>)
                
add_executable(tellwait1_8.9
                tellwait1_8.9.c
                $<TARGET_OBJECTS:aque>)

add_executable(tellwait2_8.9
                tellwait2_8.9.c
                $<TARGET_OBJECTS:aque>)

add_executable(echoall_8.10
                echoall_8.10.c
                $<TARGET_OBJECTS:aque>)      
add_executable(exec1_8.10
                exec1_8.10.c    
                $<TARGET_OBJECTS:aque>)
target_compile_definitions(exec1_8.10 PRIVATE "ROOT_DIR=${CMAKE_SOURCE_DIR}/bin/8/") 


#创建文件
set(TESTINTERP_CONTENT "#! ${CMAKE_SOURCE_DIR}/bin/7/echoarg_7.4 foo")
file(WRITE ${CMAKE_SOURCE_DIR}/bin/8/testinterp ${TESTINTERP_CONTENT})
# 变更权限
execute_process(COMMAND chmod u+x ${CMAKE_SOURCE_DIR}/bin/8/testinterp
                RESULT_VARIABLE TESTINTERP_CHMOD_RES)
if(${TESTINTERP_CHMOD_RES} EQUAL 0)
    message (SATUS " ---${CMAKE_SOURCE_DIR}/bin/8/testinterp增加执行权限成功!")
else()
    message (FATAL_ERROR "${CMAKE_SOURCE_DIR}/bin/8/testinterp增加执行权限失败!")
endif()
add_executable(exec2_8.12
                exec2_8.12.c
                $<TARGET_OBJECTS:aque>)
target_compile_definitions(exec2_8.12 PRIVATE "ROOT_DIR=${CMAKE_SOURCE_DIR}/bin/8/") 


# 复制文件
execute_process(COMMAND cp awkexample ${CMAKE_SOURCE_DIR}/bin/8
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE AWKEXAMPLE_CP_RES)
if(${AWKEXAMPLE_CP_RES} EQUAL 0)
    message (SATUS " ---${CMAKE_SOURCE_DIR}/src/8/awkexample复制到bin目录成功!")
else()
    message (FATAL_ERROR "${CMAKE_SOURCE_DIR}/src/8/awkexample复制到bin目录失败!")
endif()
# 变更权限
execute_process(COMMAND chmod u+x ${CMAKE_SOURCE_DIR}/bin/8/awkexample
                RESULT_VARIABLE AWKEXAMPLE_CHMOD_RES)
if(${AWKEXAMPLE_CHMOD_RES} EQUAL 0)
    message (SATUS " ---${CMAKE_SOURCE_DIR}/src/8/awkexample增加执行权限成功!")
else()
    message (FATAL_ERROR "${CMAKE_SOURCE_DIR}/src/8/awkexample增加执行权限失败!")
endif()

add_executable(systest1_8.13
                systest1_8.13.c
                $<TARGET_OBJECTS:aque>)

add_executable(pruids_8.13
                pruids_8.13.c
                $<TARGET_OBJECTS:aque>)
add_executable(systest3_8.13
                systest3_8.13.c
                $<TARGET_OBJECTS:aque>)

add_executable(nice_8.16
                nice_8.16.c
                $<TARGET_OBJECTS:aque>)
                