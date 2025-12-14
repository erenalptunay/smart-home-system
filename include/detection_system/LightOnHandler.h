#ifndef LIGHTONHANDLER_H
#define LIGHTONHANDLER_H

#include "EmergencyHandler.h"
#include "../device_hierarchy/Light.h"
#include <vector>

// Handles the visual warning state (light flashing).
class LightOnHandler : public EmergencyHandler {
private:
    vector<Light*> lights;

public:
    LightOnHandler(const vector<Light*>& homeLights) : lights(homeLights) {}

    void handleRequest() override {
        cout << "[System] Flashing lights..." << endl;
        
        // Flash lights 3 times to simulate warning
        for (int i = 0; i < 3; ++i) {
            cout << "Lights ON" << endl;
            // TODO: Implement actual light toggling when Light class supports it
            
            cout << "Lights OFF" << endl;
        }

        EmergencyHandler::handleRequest();
    }
};

#endif
