cmake_minimum_required(VERSION 3.16)
project(DataStructures)

set(CMAKE_CXX_STANDARD 14)

add_executable(DataStructures main.cpp datastructure/source/Queue.cpp datastructure/header/Queue.h catch.hpp)