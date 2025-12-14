#include "../../include/detection_system/LightOnHandler.h"
#include <iostream>

using namespace std;

LightOnHandler::LightOnHandler(const vector<Light*>& homeLights) : lights(homeLights) {}

void LightOnHandler::handleRequest() {
    cout << "[System] Flashing lights..." << endl;
    
    // Flash lights 3 times to simulate warning
    for (int i = 0; i < 3; ++i) {
        cout << "Lights ON" << endl;
        // TODO: Implement actual light toggling when Light class supports it
        
        cout << "Lights OFF" << endl;
    }

    EmergencyHandler::handleRequest();
}
