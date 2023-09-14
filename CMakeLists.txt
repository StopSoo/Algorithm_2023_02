cmake_minimum_required(VERSION 3.22)
project(Algorithm_2023_02)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cmake-build-debug)
include_directories(Week01)

add_executable(Algorithm_2023_02
#        Week01/stack_by_array_to_double.cpp
        Week01/stack_by_linked_list.cpp)
