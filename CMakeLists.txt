cmake_minimum_required(VERSION 3.16)
project(Binarbot)

set(CMAKE_CXX_STANDARD 20)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcompare-debug-second -w -Wno-deprecated -fPIC -latomic")
endif()

if (UNIX AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie -no-pie -g3")
endif()

set(SR_COMMON_ZLIB "" OFF CACHE INTERNAL "" FORCE)
set(SR_COMMON_ASSIMP "" OFF CACHE INTERNAL "" FORCE)
set(SR_COMMON_SDL "" OFF CACHE INTERNAL "" FORCE)
set(SR_COMMON_CURL "" ON CACHE INTERNAL "" FORCE)
set(SR_COMMON_JSON "" ON CACHE INTERNAL "" FORCE)

option(SR_COMMON_EMBED_RESOURCES "" OFF)
option(SR_COMMON_DLL_EXPORTS "" OFF)

add_subdirectory(libs/Utils)

add_executable(Binarbot Binarbot.cxx main.cpp)

target_include_directories(Binarbot PUBLIC libs/Utils/inc)
target_include_directories(Binarbot PUBLIC inc)

target_link_libraries(Binarbot Utils)