cmake_minimum_required(VERSION 3.10)

project(SmartHomeSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(SmartHomeSystem src/main.cpp 
"include/state_management/DeviceAdjustment.h"
src/storage_logging/LogService.cpp 
"include/command_pattern/CommandP.h"
src/state_management/SystemStateManager.cpp)
