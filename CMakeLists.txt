# AsyncDesign is a toy enviroment for me to play around in.
cmake_minimum_required(VERSION 3.8)

# CMake variables
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -W -Wall -Wextra -pedantic -pthread")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

project (command)

# Submodules of async_design
add_subdirectory(tools)
#add_subdirectory(thirdparty)
add_subdirectory(fpic_modules)
add_subdirectory(cmd_modules)
add_subdirectory(async_design)
