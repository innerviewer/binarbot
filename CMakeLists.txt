cmake_minimum_required(VERSION 3.16)
project(binarbot)

set(CMAKE_CXX_STANDARD 20)
set(USE_MANUAL OFF CACHE INTERNAL "" FORCE)
set(BUILD_CURL_EXE OFF CACHE INTERNAL "" FORCE)
set(BUILD_TESTING OFF CACHE INTERNAL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)
set(USE_OPENSSL ON CACHE INTERNAL "" FORCE)
set(CURL_USE_OPENSSL ON CACHE INTERNAL "" FORCE)
# set(OPENSSL_ROOT_DIR "libs/openssl")
# set(OPENSSL_INCLUDE_DIR "libs/openssl/include")
# set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_CURRENT_BINARY_DIR}/libs/openssl/include")
set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/libs/openssl/include")
# set(OPENSSL_LIBRARIES "ssl")
list(APPEND CURL_LIBS "ssl")

# list(APPEND CURL_LIBS ${OPENSSL_LIBRARIES})
# include_directories(${OPENSSL_INCLUDE_DIR})
# include_directories(${OPENSSL_INCLUDE_DIR})

add_subdirectory(libs/openssl)
add_subdirectory(libs/curl)
add_subdirectory(libs/json)

add_executable(binarbot binarbot.cxx main.cpp)

target_include_directories(binarbot PUBLIC libs/openssl/include)
target_include_directories(binarbot PUBLIC libs/curl/include)
target_include_directories(binarbot PUBLIC libs/json/include)
target_include_directories(binarbot PUBLIC inc)

target_link_libraries(binarbot nlohmann_json curlu ssl libcurl)