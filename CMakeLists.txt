cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hello-googletest)

enable_testing()

add_subdirectory(lib)
add_subdirectory(test)
