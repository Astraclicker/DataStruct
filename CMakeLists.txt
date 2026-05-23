cmake_minimum_required(VERSION 4.1)
project(DataStruct)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(
        DataStruct
        ${CMAKE_SOURCE_DIR}/src/main.cpp
)
