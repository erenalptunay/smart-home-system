cmake_minimum_required(VERSION 3.10)

project(SmartHomeSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enforce UTF-8 encoding for MSVC
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Include directories
include_directories(include)

# Main program
add_executable(SmartHomeSystem src/main.cpp 
    "include/state_management/DeviceAdjustment.h"
    src/storage_logging/LogService.cpp 
    "include/command_pattern/CommandP.h"
    src/state_management/SystemStateManager.cpp
    src/detection_system/EmergencyHandler.cpp
    src/detection_system/AlarmHandler.cpp
    src/detection_system/LightOnHandler.cpp
    src/detection_system/FireCallHandler.cpp
    src/security_system/AlarmHandlerF.cpp
    src/security_system/SecuritySystem.cpp
    src/security_system/PoliceCallHandler.cpp
    src/security_system/LightOnHandler.cpp)

# Test executable - Security
add_executable(SmartHomeSystemSecurityTests
    src/security_system/test.cpp
    src/security_system/SecuritySystem.cpp
    src/security_system/PoliceCallHandler.cpp
    src/security_system/AlarmHandlerF.cpp
    src/security_system/LightOnHandler.cpp
 )

# Test executable - Device
add_executable(SmartHomeSystemDeviceTest src/device_hierarchy/test.cpp )

# Test executable - Detection
add_executable(SmartHomeSystemDetectionTest 
    src/detection_system/test.cpp
    src/detection_system/EmergencyHandler.cpp
    src/detection_system/AlarmHandler.cpp
    src/detection_system/LightOnHandler.cpp
    src/detection_system/FireCallHandler.cpp
    src/detection_system/ObservableDetector.cpp)

# Test executable - Log
add_executable(SmartHomeSystemLogTest 
    src/storage_logging/test.cpp
    src/storage_logging/LogService.cpp 
)

# Test executable - Mode
add_executable(SmartHomeSystemModeTest 
    src/mode_management/test.cpp
)

# Test executable - State
add_executable(SmartHomeSystemStateTest 
    src/state_management/test.cpp
    src/state_management/SystemStateManager.cpp
)