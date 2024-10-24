cmake_minimum_required(VERSION 3.10)

# Project Name
project(Algorithm-Visualizer)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

# Add the main executable
add_executable(Algorithm-Visualizer main.cpp Queue.hpp linkedList.hpp)

# Find the SFML package (installed globally)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Link SFML libraries to the executable
target_link_libraries(Algorithm-Visualizer sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
