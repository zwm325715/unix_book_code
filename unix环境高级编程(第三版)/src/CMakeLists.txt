#CHAPTER在shell中传入
if(CHAPTER STREQUAL "all") 
    add_subdirectory(1)
    add_subdirectory(2)
elseif(CHAPTER STREQUAL "1")
    add_subdirectory(1)
elseif(CHAPTER STREQUAL "2")    
    add_subdirectory(2)
endif()
