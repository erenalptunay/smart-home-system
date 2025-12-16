#ifndef ALARMHANDLER_H
#define ALARMHANDLER_H

#include "EmergencyHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h> // For _kbhit() and _getch() on Windows
#endif

// Handles the alarm state in the emergency sequence.
class AlarmHandler : public EmergencyHandler {
public:
    void handleRequest() override;
};

#endif
