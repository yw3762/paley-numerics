cmake_minimum_required(VERSION 3.27)
project(paley_l3)

set(CMAKE_CXX_STANDARD 20)

add_executable(paley_l3 main.cpp
        helpers.cpp
        lovasz.cpp
        block_diagonal.cpp)
