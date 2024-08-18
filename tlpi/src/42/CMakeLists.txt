#编译生成的可执行文件放在bin/42目录下
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/42)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/42)

add_executable(dynload_42.1
                dynload_42.1.c
                $<TARGET_OBJECTS:tlpi>)
target_link_libraries(dynload_42.1 -ldl)
# ------------------42.3.1--------
set(VIS_LIST 
    42.3.1/vis_comm_42.3.1.c
    42.3.1/vis_f1_42.3.1.c
    42.3.1/vis_f2_42.3.1.c
    )
add_library(vis SHARED ${VIS_LIST})
list(APPEND vis_compile_flags "-g" "-Wall" "-fPIC" "-Wunused-variable")
target_compile_options(vis PRIVATE ${vis_compile_flags})
#增加链接选项，不导出vis_comm
target_link_options(vis PRIVATE "-Wl,--version-script,${CMAKE_CURRENT_LIST_DIR}/42.3.1/vis.map")

# ------------------42.3.2--------
# 1-1.构建动态库libsv.so
# set(SV_V1_LIST 
#     42.3.2/sv_lib_v1.c
#     )
# add_library(sv SHARED ${SV_V1_LIST})
# list(APPEND sv_v1_compile_flags "-g" "-Wall" "-fPIC")
# #编译选项
# target_compile_options(sv PRIVATE ${sv_v1_compile_flags})
# #增加链接选项
# target_link_options(sv PRIVATE "-Wl,--version-script,${CMAKE_CURRENT_LIST_DIR}/42.3.2/sv_v1.map")
# #1-2.创建一个程序p1(sv_prog.c)来使用这个库
# add_executable(p1
#                 42.3.2/sv_prog.c)
# #链接libsv.so
# target_link_libraries(p1 PUBLIC sv)

#2-1.构建库的新版本
set(SV_V2_LIST 
    42.3.2/sv_lib_v2.c
    )
add_library(sv SHARED ${SV_V2_LIST})
list(APPEND sv_v2_compile_flags "-g" "-Wall" "-fPIC")
#编译选项
target_compile_options(sv PRIVATE ${sv_v2_compile_flags})
#增加链接选项
target_link_options(sv PRIVATE "-Wl,--version-script,${CMAKE_CURRENT_LIST_DIR}/42.3.2/sv_v2.map")
#2-2.创建一个程序p2(sv_prog.c)来使用这个库
add_executable(p2
                42.3.2/sv_prog.c)
#链接libsv.so
target_link_libraries(p2 PUBLIC sv)

