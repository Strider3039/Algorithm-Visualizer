cmake_minimum_required(VERSION 3.10)

# Project Name
project(Algorithm-Visualizer)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

# Add the main executable
add_executable(Algorithm-Visualizer main.cpp)

# Find the SFML package (installed globally)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Link SFML libraries to the executable
target_link_libraries(Algorithm-Visualizer sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# Find X11 package
find_package(X11 REQUIRED)

# Link X11 library
target_link_libraries(Algorithm-Visualizer ${X11_LIBRARIES})