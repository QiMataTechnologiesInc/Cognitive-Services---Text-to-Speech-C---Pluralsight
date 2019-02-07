cmake_minimum_required(VERSION 3.13)
project(texttospeech)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_USE_OPENSSL ON)

add_subdirectory(lib/cpr)
include_directories(${CPR_INCLUDE_DIRS})

add_executable(texttospeech main.cpp)

target_link_libraries(texttospeech ${CPR_LIBRARIES})