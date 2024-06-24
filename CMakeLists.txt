cmake_minimum_required(VERSION 3.16)
project(Binarbot)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX")
endif()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /utf-8")
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcompare-debug-second -w -Wno-deprecated -fPIC -latomic")
endif()

add_definitions(
        -DSR_DLL_EXPORTS
        -DSR_SUPPORT_PARALLEL
        -DSR_CXX_20
)

if (UNIX AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie -no-pie -g3")
endif()

set(SR_COMMON_ZLIB OFF)
set(SR_COMMON_ASSIMP OFF)
set(SR_COMMON_SDL OFF)
set(SR_COMMON_CURL ON)
set(SR_COMMON_JSON ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSR_DLL_EXPORTS")
set(SR_COMMON_DLL_EXPORTS ON)
set(SR_COMMON_CI_BUILD OFF)
set(SR_COMMON_EMBED_RESOURCES OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
SET(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
SET(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)

set(CMAKE_BUILD_PARALLEL_LEVEL 0)

add_subdirectory(libs/Utils)

add_executable(Binarbot Binarbot.cxx main.cpp)

target_link_libraries(Binarbot Utils)

target_include_directories(Binarbot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)