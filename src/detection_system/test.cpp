#include <iostream>
#include <vector>
#include "../../include/detection_system/AlarmHandler.h"
#include "../../include/detection_system/LightOnHandler.h"
#include "../../include/detection_system/FireCallHandler.h"
#include "../../include/detection_system/ObservableDetector.h"
#include "../../include/device_hierarchy/Light.h"

using namespace std;

// Define static members here for the isolated test to link correctly
int Device::idCounter = 0;
int SmokeDetector::smokeId = 0;
int Light::lightId = 0;

int main() {
    cout << "=== Detection System Test (Isolated) ===" << endl;

    // 1. Setup Devices
    vector<Light*> homeLights;
    homeLights.push_back(new Light("Living Room Light"));
    homeLights.push_back(new Light("Kitchen Light"));

    ObservableSmokeDetector* smokeDetector = new ObservableSmokeDetector("Main Hall Smoke Detector");

    // 2. Setup Chain of Responsibility
    AlarmHandler* alarm = new AlarmHandler();
    LightOnHandler* lightsHandler = new LightOnHandler(homeLights);
    FireCallHandler* fireCall = new FireCallHandler();

    // Chain: Alarm -> Lights -> Fire Call
    alarm->setNext(lightsHandler);
    lightsHandler->setNext(fireCall);

    // 3. Attach Observer
    // The chain starts with the AlarmHandler
    smokeDetector->attach(alarm);

    // 4. Test Scenario 1: Full Sequence
    cout << "\n--- Test Scenario 1: Full Sequence (No Interrupt) ---" << endl;
    cout << "Instructions: When prompted, enter any key (NOT 's') to simulate timeout." << endl;
    smokeDetector->detectSmoke();

    // 5. Test Scenario 2: Interrupted Sequence
    cout << "\n--- Test Scenario 2: User Interrupts Alarm ---" << endl;
    cout << "Instructions: When prompted, enter 's' to stop the alarm." << endl;
    smokeDetector->detectSmoke();

    // Cleanup
    delete smokeDetector;
    delete alarm; 
    
    for (auto light : homeLights) {
        delete light;
    }

    return 0;
}
