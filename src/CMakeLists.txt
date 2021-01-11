# On MSVC remove /W3, as we are replacing it with /W4. Could be removed as of
# 3.15 with this: https://cmake.org/cmake/help/latest/policy/CMP0092.html
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
    string(REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# On Windows enable UNICODE/_UNICODE macros to avoid accidentally passing UTF-8
# values to ANSI functions
if(CORRADE_TARGET_WINDOWS)
    add_definitions("-DUNICODE" "-D_UNICODE")
endif()

add_subdirectory(main)
# add_subdirectory(main_vulkan)
