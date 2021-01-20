cmake_minimum_required(VERSION 3.12)

set(srcDir ${CMAKE_SOURCE_DIR}/3rd-party/lua)

set(SRC_CORE
    lapi.c
    lcode.c
    lctype.c
    ldebug.c
    ldo.c
    ldump.c
    lfunc.c
    lgc.c
    llex.c
    lmem.c
    lobject.c
    lopcodes.c
    lparser.c
    lstate.c
    lstring.c
    ltable.c
    ltests.c
    ltm.c
    lundump.c
    lvm.c
    lzio.c)
set(SRC_LIB
    lauxlib.c
    lbaselib.c
    lcorolib.c
    ldblib.c
    liolib.c
    lmathlib.c
    loadlib.c
    loslib.c
    lstrlib.c
    ltablib.c
    lutf8lib.c
    linit.c)

set(SRC_LUA lua.c)
# set(SRC_LUAC luac.c)

set(HEADERS lauxlib.h lua.h luaconf.h lualib.h)

list(TRANSFORM SRC_CORE PREPEND ${srcDir}/)
list(TRANSFORM SRC_LIB PREPEND ${srcDir}/)
list(TRANSFORM SRC_LUA PREPEND ${srcDir}/)
# list(TRANSFORM SRC_LUAC PREPEND ${srcDir}/)
list(TRANSFORM HEADERS PREPEND ${srcDir}/)

set(CMAKE_C_STANDARD 99)
set(CMAKE_SHARED_LINKER_FLAGS "-Wl" ${CMAKE_SHARED_LINKER_FLAGS})

add_compile_options(
    -Wextra
    -Wshadow
    -Wsign-compare
    -Wundef
    -Wwrite-strings
    -Wredundant-decls
    -Wdisabled-optimization
    -Waggregate-return
    -Wdouble-promotion
    -Wdeclaration-after-statement
    -Wmissing-prototypes
    -Wnested-externs
    -Wstrict-prototypes
    -Wc++-compat
    -Wold-style-definition
    -Wold-style-cast
    -fno-stack-protector
    -fno-common
    -march=native
)

add_library(lua-lib ${SRC_CORE} ${SRC_LIB})
target_compile_definitions(
    lua-lib PRIVATE
    $<$<PLATFORM_ID:Linux>:LUA_USE_LINUX LUA_COMPAT_5_2>
    $<$<PLATFORM_ID:Windows>:LUA_BUILD_AS_DLL _CRT_SECURE_NO_WARNINGS>
    $<$<PLATFORM_ID:MacOS>:LUA_USE_LINUX>
)
set_target_properties(lua-lib PROPERTIES OUTPUT_NAME lua)

add_library(lua-sharedlib SHARED ${SRC_CORE} ${SRC_LIB})
target_compile_definitions(
    lua-sharedlib PRIVATE
    $<$<PLATFORM_ID:Linux>:LUA_USE_LINUX LUA_COMPAT_5_2>
    $<$<PLATFORM_ID:Windows>:LUA_BUILD_AS_DLL _CRT_SECURE_NO_WARNINGS>
    $<$<PLATFORM_ID:MacOS>:LUA_USE_LINUX>
)
set_target_properties(lua-sharedlib PROPERTIES OUTPUT_NAME lua)

set(includeDir ${CMAKE_CURRENT_BINARY_DIR}/include)
file(COPY ${HEADERS} DESTINATION ${includeDir})

add_library(lua-header INTERFACE)

target_include_directories(lua-header INTERFACE ${includeDir})

target_link_libraries(lua-lib INTERFACE lua-header)
target_link_libraries(lua-sharedlib INTERFACE lua-header)

add_executable(luaexec ${SRC_LUA})
target_link_libraries(luaexec lua-lib)
set_target_properties(luaexec PROPERTIES OUTPUT_NAME lua)

add_library(lua::lib ALIAS lua-lib)
add_library(lua::sharedlib ALIAS lua-sharedlib)
add_library(lua::header ALIAS lua-header)

set(LUA_INCLUDE_DIR ${includeDir})
set(LUA_LIBRARIES lua::lib)

mark_as_advanced(${LUA_INCLUDE_DIR})
