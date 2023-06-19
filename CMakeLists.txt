cmake_minimum_required(VERSION 3.26)
project(graph)

set(CMAKE_CXX_STANDARD 20)
set(FOO "true")

add_executable(graph main.cpp)
target_link_libraries(graph PRIVATE -fsanitize=undefined)
target_compile_options(graph PRIVATE -fsanitize=undefined)
