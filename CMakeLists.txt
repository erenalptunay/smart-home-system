cmake_minimum_required(VERSION 3.10)

project(SmartHomeSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(SmartHomeSystem src/main.cpp)

# Test executable
add_executable(SmartHomeSystemTests src/security_system/test.cpp)

# If "include/security_system/Üst Bilgi1.h" is a header, it should not be listed as a source file.
# CMake expects only source files (.cpp, .c, etc.) in add_executable.
