cmake_minimum_required(VERSION 3.5)

# my project name
project(DataStructures)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructures main.cpp)

add_subdirectory("TestingUtils")
add_subdirectory("DataStructure")
# get info about lib
include(TestingUtils/info.cmake)
PrintInfo()

target_link_libraries(${PROJECT_NAME} TestingUtils DataStructure)

target_compile_options(DataStructures PRIVATE -Wall -Werror -pedantic -Wsign-conversion -Wconversion) # -Wextra

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

message("Done")






