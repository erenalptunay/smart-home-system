#ifndef ALARMHANDLER_H
#define ALARMHANDLER_H

#include "EmergencyHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

// Handles the alarm state in the emergency sequence.
class AlarmHandler : public EmergencyHandler {
public:
    void handleRequest() override {
        cout << "[System] Alarm activated for 10 seconds..." << endl;
        
        // Simulates alarm duration. Blocking wait for initial implementation.
        cout << "[System] Press 's' to stop the alarm, or any other key to continue (Simulated input)..." << endl;
        char input;
        cout << "> ";
        cin >> input;

        if (input == 's' || input == 'S') {
            cout << "[System] Alarm stopped by user. Sequence interrupted." << endl;
        } else {
            cout << "[System] No interruption. Proceeding to next step..." << endl;
            EmergencyHandler::handleRequest();
        }
    }
};

#endif
