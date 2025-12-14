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
    LightOnHandler(const vector<Light*>& homeLights);

    void handleRequest() override;
};

#endif
