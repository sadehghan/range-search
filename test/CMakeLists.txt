cmake_minimum_required(VERSION 2.6)

project(range-search-test)

include_directories(..)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

add_executable(range-search-test RangeSearchTest.cpp)
