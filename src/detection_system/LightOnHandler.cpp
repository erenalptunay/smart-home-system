#include "../../include/detection_system/LightOnHandler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h> // For _kbhit and _getch (Windows)

using namespace std;

LightOnHandler::LightOnHandler(const vector<Light*>& homeLights) : lights(homeLights) {}

void LightOnHandler::handleRequest() {
    cout << "[System] Flashing lights... (Press 's' to stop)" << endl;
    
    bool interrupted = false;
    // Flash lights 5 times with 1 second interval (Reduced to half)
    for (int i = 0; i < 5; ++i) {
        cout << "Lights ON" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        cout << "Lights OFF" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Check for user interrupt (LLR-44, LLR-45)
        if (_kbhit()) {
            char input = _getch();
            if (input == 's' || input == 'S') {
                cout << "\n[System] Light sequence stopped by user." << endl;
                cout << "[System] Fire Station was NOT notified." << endl;
                interrupted = true;
                break;
            }
        }
    }

    if (!interrupted) {
        EmergencyHandler::handleRequest();
    }
}
