cmake_minimum_required(VERSION 3.8)

project(SNAKE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(SNAKE Game.cpp)  
add_subdirectory ("SNAKE")
