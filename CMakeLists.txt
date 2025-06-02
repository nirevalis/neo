cmake_minimum_required(VERSION 3.10)
project(neovalis VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(lib)
add_subdirectory(example)