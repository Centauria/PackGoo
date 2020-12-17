cmake_minimum_required(VERSION 3.12)

project("PerfectDelivery" VERSION 0.1)

# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_THREAD_SAFE")
file(GLOB HEADER_FILES CONFIGURE_DEPENDS "include/*.h")
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp" "main.cpp")

include_directories(include)
link_directories(lib)

add_subdirectory(3rd-party/spdlog)
find_package(spdlog REQUIRED)

add_subdirectory(3rd-party/sol2)
find_package(sol2 REQUIRED)

find_package(Lua53 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} spdlog sol2)
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIB})
