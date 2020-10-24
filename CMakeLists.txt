cmake_minimum_required(VERSION 3.16)

# my project name
project(DataStructures VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# a header file so does not have to be linked
add_subdirectory("TestingUtils")
# implementation of the Queue data structure
add_subdirectory("DataStructure")
# A math Utility Lib that I want to link as .so file
add_subdirectory("HelperLib")

# Headers cannot be libraries, so I will have to refactor where possible
add_executable(QueueTest main.cpp TestingUtils/catch.hpp DataStructure/header/Queue.h)

# get info about lib
include(TestingUtils/info.cmake)
PrintInfo()

target_link_libraries(QueueTest
        PRIVATE MathUtils)

target_compile_options(QueueTest PRIVATE -Wall -Werror -pedantic -Wsign-conversion -Wconversion) # -Wextra

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

message("Done")






