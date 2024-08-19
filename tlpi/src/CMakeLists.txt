#CHAPTER在shell中传入
if(CHAPTER STREQUAL "all") 
    add_subdirectory(42)
    add_subdirectory(49)
elseif(CHAPTER STREQUAL "42")
    add_subdirectory(42)
elseif(CHAPTER STREQUAL "49")
    add_subdirectory(49)
endif()
