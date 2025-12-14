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
        cout << "[Sistem] Işıklar acil durum için kapanıp açılıyor..." << endl;
        
        // Flash lights 3 times to simulate warning
        for (int i = 0; i < 3; ++i) {
            cout << "Işıklar açık!" << endl;
            // TODO: Implement actual light toggling when Light class supports it
            
            cout << "Işıklar kapalı!" << endl;
        }

        EmergencyHandler::handleRequest();
    }
};

#endif
