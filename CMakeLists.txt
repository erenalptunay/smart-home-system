cmake_minimum_required(VERSION 3.10)

project(SmartHomeSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Test executable
add_executable(SmartHomeSystemSecurityTests
    src/security_system/test.cpp
    src/security_system/SecuritySystem.cpp
    src/security_system/PoliceCallHandler.cpp
    src/security_system/AlarmHandler.cpp
    src/security_system/LightOnHandler.cpp
)

# If "include/security_system/�st Bilgi1.h" is a header, it should not be listed as a source file.
# CMake expects only source files (.cpp, .c, etc.) in add_executable.
#Main program
add_executable(SmartHomeSystem src/main.cpp 
"include/state_management/DeviceAdjustment.h"
src/storage_logging/LogService.cpp 
"include/command_pattern/CommandP.h"
src/state_management/SystemStateManager.cpp
)
# Add device test configuration
add_executable(SmartHomeSystemDeviceTest src/device_hierarchy/test.cpp)
