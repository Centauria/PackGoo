cmake_minimum_required(VERSION 3.0.0)
project(PackGoo VERSION 0.1.0)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-D_THREAD_SAFE" ${CMAKE_CXX_FLAGS})

set(CMAKE_LIBRARY_ARCHITECTURE x64)
set(FIND_LIBRARY_USE_LIB64_PATHS TRUE)

add_subdirectory(3rd-party/corrade EXCLUDE_FROM_ALL)
set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
set(WITH_VK ON CACHE BOOL "" FORCE)
set(WITH_SHADERTOOLS ON CACHE BOOL "" FORCE)
# option(TARGET_VK ON)
add_subdirectory(3rd-party/magnum EXCLUDE_FROM_ALL)
find_package(Magnum REQUIRED)

add_subdirectory(3rd-party/spdlog EXCLUDE_FROM_ALL)
add_subdirectory(3rd-party/sol2 EXCLUDE_FROM_ALL)

find_package(Lua54 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(3rd-party/json EXCLUDE_FROM_ALL)

add_subdirectory(src)
