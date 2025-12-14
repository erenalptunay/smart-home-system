cmake_minimum_required(VERSION 3.10)

project(SmartHomeSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(SmartHomeSystem src/main.cpp 
"include/state_management/DeviceController.h"
src/storage_logging/LogService.cpp)

add_executable(SmartHomeSystemDetectionTest 
    src/detection_system/test.cpp
    src/detection_system/EmergencyHandler.cpp
    src/detection_system/AlarmHandler.cpp
    src/detection_system/LightOnHandler.cpp
    src/detection_system/FireCallHandler.cpp
    src/detection_system/ObservableDetector.cpp
)