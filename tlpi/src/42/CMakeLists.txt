#编译生成的可执行文件放在bin/42目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/42)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/42)

add_executable(dynload_42.1
                dynload_42.1.c
                $<TARGET_OBJECTS:tlpi>)
target_link_libraries(dynload_42.1 -ldl)

set(VIS_LIST 
    vis_comm_42.3.1.c
    vis_f1_42.3.1.c
    vis_f2_42.3.1.c
    )
add_library(vis SHARED ${VIS_LIST})
list(APPEND vis_compile_flags "-g" "-Wall" "-fPIC" "-Wunused-variable")
target_compile_options(vis PRIVATE ${vis_compile_flags})
#增加链接选项，不导出vis_comm
target_link_options(vis PRIVATE "-Wl,--version-script,${CMAKE_CURRENT_LIST_DIR}/vis.map")