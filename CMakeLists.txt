cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(parser)

# add the executable
add_executable(parser main.cpp state.cpp tree.cpp state_machine.cpp node.cpp)