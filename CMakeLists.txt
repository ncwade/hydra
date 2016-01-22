cmake_minimum_required(VERSION 3.0)
project(hydra)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fcolor-diagnostics")

find_package(BOOST)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(vendor/path_finder/src)

add_subdirectory(vendor/path_finder)
add_subdirectory(test)
