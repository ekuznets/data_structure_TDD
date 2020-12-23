cmake_minimum_required(VERSION 3.16)

if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR
        "In-source Builds are not allowed
        Please run:
        rm -rf CMakeCache.txt CMakeFiles
        then create a build/ directory and retry")
endif()

# my project name
project(DataStructures VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# a header file so does not have to be linked
add_subdirectory("TestingUtils")
# implementation of the Queue data structure
add_subdirectory("DataStructure")

# Headers cannot be libraries, so I will have to refactor where possible
set(projectName QueueTest.elf)
add_executable(${projectName} main.cpp TestingUtils/catch.hpp)

# get info about lib
include(TestingUtils/info.cmake)
PrintInfo()

# A math Utility Lib that I want to link as .so file
target_link_libraries(${projectName} ${CMAKE_SOURCE_DIR}/res/libMathUtils.so QueueDT)

target_compile_options(${projectName} PRIVATE -Wall -Werror -pedantic -Wsign-conversion -Wconversion) # -Wextra

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

message("Done")
