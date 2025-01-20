set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin/4)
add_executable(4.1_copy
              4.1_copy.c
              $<TARGET_OBJECTS:tlpi>)
               