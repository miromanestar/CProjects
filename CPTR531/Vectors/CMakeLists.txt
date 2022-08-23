cmake_minimum_required(VERSION 3.11.0)
project(vector VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra)

add_executable(vector simplevectortest.cpp vectorutils.cpp)