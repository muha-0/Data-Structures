cmake_minimum_required(VERSION 3.10)
project(DataStructures CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(data_structures main.cpp)
