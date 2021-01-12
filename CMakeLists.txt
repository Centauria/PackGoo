cmake_minimum_required(VERSION 3.0.0)
project(PackGoo VERSION 0.1.0)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})
if(MSVC OR MINGW)
    set(CMAKE_PREFIX_PATH "E:\\Portable\\SDL2-2.0.12" ${CMAKE_PREFIX_PATH})
    set(CMAKE_PREFIX_PATH "D:\\PF\\VulkanSDK\\1.2.162.0" ${CMAKE_PREFIX_PATH})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-D_THREAD_SAFE" ${CMAKE_CXX_FLAGS})

set(CMAKE_LIBRARY_ARCHITECTURE x64)
set(FIND_LIBRARY_USE_LIB64_PATHS TRUE)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(3rd-party/corrade EXCLUDE_FROM_ALL)
set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
set(WITH_VK ON CACHE BOOL "" FORCE)
set(WITH_SHADERTOOLS ON CACHE BOOL "" FORCE)
# option(TARGET_VK ON)
add_subdirectory(3rd-party/magnum EXCLUDE_FROM_ALL)

add_subdirectory(3rd-party/spdlog EXCLUDE_FROM_ALL)

set(SOL2_LUA_VERSION 5.4.2)
add_subdirectory(3rd-party/sol2 EXCLUDE_FROM_ALL)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(3rd-party/json EXCLUDE_FROM_ALL)

add_subdirectory(src)
